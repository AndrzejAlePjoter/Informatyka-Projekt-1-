#include "Pilka.h"
#include <cmath>
#include <iostream>

Pilka::Pilka(float startX, float startY, float startVx, float startVy, float r)
    : x(startX), y(startY), vx(startVx), vy(startVy), radius(r)
{
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::move() {
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX() { vx = -vx; }
void Pilka::bounceY() { vy = -vy; }

void Pilka::collideWalls(float width, float height) {
    // Lewa
    if (x - radius < 0) {
        x = radius;
        bounceX();
    }
    // Prawa
    else if (x + radius > width) {
        x = width - radius;
        bounceX();
    }
    // Góra
    if (y - radius < 0) {
        y = radius;
        bounceY();
    }
    // Dó³ (Game Over) obs³ugiwany w Game.cpp
}

bool Pilka::collidePaddle(const Paletka& p) {
    float palX = p.getX();
    float palY = p.getY();
    float palW = p.getSzerokosc();
    float palH = p.getWysokosc();

    // Warunek poziomy
    bool hitX = (x >= palX - palW / 2.f) && (x <= palX + palW / 2.f);

    // Warunek pionowy
    // Margines b³êdu
    bool hitY = (y + radius >= palY - palH / 2.f) && (y - radius < palY - palH / 2.f);

    if (hitX && hitY) {
        vy = -std::abs(vy); // Odbij w górê
        y = (palY - palH / 2.f) - radius - 1.f; // Wyci¹gnij pi³kê z paletki
        shape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::reset(float newX, float newY, float newVx, float newVy) {
    x = newX;
    y = newY;
    vx = newVx;
    vy = newVy;
    shape.setPosition(x, y);
}

void Pilka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}