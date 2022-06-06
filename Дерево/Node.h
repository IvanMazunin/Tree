#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Node {
private:
    double str; 
    int x;
    int y; 
    CircleShape circle; 
    int radius;
    Font font;
    Text text;
public:
    Node() {}

    Node(double str, int radius, int x, int y) {
        this->str = str;
        this->radius = radius;
        this->x = x;
        this->y = y;

        circle.setRadius(radius);
        circle.setPosition(x - radius, y - radius);
        circle.setFillColor(sf::Color(139, 69, 19));

        font.loadFromFile("Bahnschrift.ttf");
        text.setFillColor(sf::Color::White);
        text.setString(to_string(int(str)));
        text.setFont(font);
        text.setCharacterSize(radius);
        text.setOutlineColor(Color::Red);
        text.setPosition(x - 0.55 * text.getGlobalBounds().width, y - 0.9 * text.getGlobalBounds().height);
    }
    
    Node(const Node& node) {
        this->str = node.str;
        this->radius = node.radius;
        this->x = node.x;
        this->y = node.y;
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }

    int GetRadius() {
        return radius;
    }

    void Draw(sf::RenderWindow& window) {
        window.draw(this->circle);
        window.draw(this->text);
    }
};
