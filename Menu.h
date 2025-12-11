#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define MAX_ITEMS 4 // Nowa gra, Wczytaj, Wyniki, Wyjœcie

class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuItems[MAX_ITEMS];

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getPressedItem() const { return selectedItemIndex; }
};