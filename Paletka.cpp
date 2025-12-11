#include "Paletka.h"

Paletka::Paletka(float startX, float startY, float w, float h, float speed)
    : x(startX), y(startY), szerokosc(w), wysokosc(h), predkosc(speed)
{
    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Cyan);
}

void Paletka::moveLeft() {
    x -= predkosc;
    shape.setPosition(x, y);
}

void Paletka::moveRight() {
    x += predkosc;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float windowWidth) {
    if (x - szerokosc / 2.f < 0) {
        x = szerokosc / 2.f;
    }
    if (x + szerokosc / 2.f > windowWidth) {
        x = windowWidth - szerokosc / 2.f;
    }
    shape.setPosition(x, y);
}

void Paletka::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}