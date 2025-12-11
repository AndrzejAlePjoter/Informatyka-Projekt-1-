#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float startX, float startY, float startVx, float startVy, float r);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(const Paletka& p);

    void draw(sf::RenderTarget& target);

    // Metoda do resetowania/ustawiania stanu (Load Game)
    void reset(float newX, float newY, float newVx, float newVy);

    // Gettery
    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};