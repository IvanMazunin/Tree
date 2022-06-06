#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <list>
#include "Node.h"
#include "Tree.h"
#include "Way.h"

using namespace std;
using namespace sf;

class  TreeMap {
private:
    Tree tree;
public:
   TreeMap() {}

   TreeMap(const Tree& tree) {
        this->tree = tree;
    }

    void DrawWay(RenderWindow& window, Tree tree, int x1, int x2, int y) {
        int centerx = (x1 + x2) / 2;
        Tree* lefttree = tree.GetLeft();
        if (lefttree != nullptr) {
            int leftx = (x1 + centerx) / 2;
            int lefty = y + 100;
            Way left(centerx, y, leftx, lefty, Color::Black);
            left.Draw(window);
            DrawWay(window, *lefttree, x1, centerx, lefty);
        }
        Tree* righttree = tree.GetRight();
        if (righttree != nullptr) {
            int rightx = (centerx + x2) / 2;
            int righty = y + 100;
            Way right(centerx, y, rightx, righty, Color::Black);
            right.Draw(window);
            DrawWay(window, *righttree, centerx, x2, righty);
        }
    }

    void DrawVertex(RenderWindow& window, Tree tree, int x1, int x2, int y) {
        Node a(tree.Data(), 40, (x1 + x2) / 2, y);
        a.Draw(window);
        Tree* left = tree.GetLeft();
        if (left != nullptr) {
            DrawVertex(window, *left, x1, (x1 + x2) / 2, y + 100);
        }
        Tree* right = tree.GetRight();
        if (right != nullptr)
            DrawVertex(window, *right, (x1 + x2) / 2, x2, y + 100);
    }

    void DrawTree(RenderWindow& window) {
        DrawWay(window, tree, 0, 1200, 100);
        DrawVertex(window, tree, 0, 1200, 100);
    }

    void Draw(RenderWindow& window) {
        DrawTree(window);
    }
};
