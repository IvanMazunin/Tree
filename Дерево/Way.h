#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

const double PI = 3.141592653589793; 

class Way {
private:
    int X1, Y1, X2, Y2;
    int len; 
    Color color; 
public:
   
    Way(const int& X1, const int& Y1, const int& X2, const int& Y2, Color color) {
        this->X1 = X1;
        this->Y1 = Y1;
        this->X2 = X2;
        this->Y2 = Y2;
        this->color = color;
    }

   
    void Draw(sf::RenderWindow& window) {
       
        VertexArray line(sf::LinesStrip, 2);
        line[0].position.x = X1;
        line[0].position.y = Y1;
        line[0].color = color;
        line[1].position.x = X2;
        line[1].position.y = Y2;
        line[1].color = color;
        window.draw(line);

      
        double Rotation = PI; 
        if (X2 - X1 > 0)
            Rotation = atan((double)(Y2 - Y1) / (double)(X2 - X1)) + PI / 2;
        else if (X2 - X1 < 0)
            Rotation = atan((double)(Y2 - Y1) / (double)(X2 - X1)) - PI / 2;
        else if (Y2 - Y1 < 0)
            Rotation = 0;

        int PositionX = X2 - 40 * sin(Rotation) - 8 * cos(Rotation); 
        int PositionY = Y2 + 40 * cos(Rotation) - 8 * sin(Rotation);

        sf::CircleShape triangle(8, 3);
        triangle.setRotation(180 * Rotation / PI);
        triangle.setPosition(PositionX, PositionY);
        triangle.setFillColor(color);
        window.draw(triangle);
    }
};
