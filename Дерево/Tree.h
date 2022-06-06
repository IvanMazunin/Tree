#pragma once
#include <vector>
#include <iostream>


using namespace std;

template <typename T>
vector<T> CutVector(vector<T> mas, int a, int b) {
    vector<T> mas2 = vector<T>(b - a);
    for (int i = a; i < b; i++)
        mas2[i - a] = mas[i];
    return mas2;
}

class Tree {
    friend class BalancedTree;
private:
    int data;
    Tree* Left = nullptr;
    Tree* Right = nullptr;
    Tree* Up = nullptr;
    int size = 0;
public:
    Tree() {}

    Tree(int data) {
        this->data = data;
        size = 1;
    }

    Tree(vector<int> mas) {
        this->data = mas[mas.size() / 2];

        if (mas.size() / 2 > 1)
            Left = new Tree(CutVector(mas, 0, mas.size() / 2));
        else
            Left = new Tree(mas[0]);
        Left->Up = this;
        this->size += Left->size;

        if (mas.size() - mas.size() / 2 - 1 > 1) {
            Right = new Tree(CutVector(mas, mas.size() / 2 + 1, mas.size()));
            Right->Up = this;
            this->size += Right->size;
        }
        else if (mas.size() - mas.size() / 2 - 1 == 1) {
            Right = new Tree(mas[mas.size() - 1]);
            Right->Up = this;
            this->size += Right->size;
        }
        this->size++;
    }

    Tree(const Tree& tree) {
        this->data = tree.data;
        this->size = tree.size;

        if (tree.Left != nullptr) {
            this->Left = new Tree(*tree.Left);
            this->Left->Up = this;
        }
        if (tree.Right != nullptr) {
            this->Right = new Tree(*tree.Right);
            this->Right->Up = this;
        }
    }

    Tree& operator = (const Tree& tree) {
        this->Del();
        this->data = tree.data;
        this->size = tree.size;

        if (tree.Left != nullptr) {
            this->Left = new Tree(*tree.Left);
            this->Left->Up = this;
        }
        if (tree.Right != nullptr) {
            this->Right = new Tree(*tree.Right);
            this->Right->Up = this;
        }

        return *this;
    }

    int Data() { return data; }
    int Size() { return size; }
    Tree* GetLeft() { return Left; }
    Tree* GetRight() { return Right; }

    void Del() {
        if (Left != nullptr)
            delete Left;
        if (Right != nullptr)
            delete Right;
    }

    void Print() {
        cout << data << ' ';
        if (Left != nullptr)
            Left->Print();
        if (Right != nullptr)
            Right->Print();
    }

    ~Tree() {
        this->Del();
    }
};

