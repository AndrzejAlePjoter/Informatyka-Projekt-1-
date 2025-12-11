#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float startX, float startY, float w, float h, float speed);

    void moveLeft();
    void moveRight();
    void clampToBounds(float windowWidth);
    void draw(sf::RenderTarget& target);

    // Settery (potrzebne do wczytywania stanu gry)
    void setPosition(float newX, float newY);

    // Gettery
    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};