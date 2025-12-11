#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Nie udalo sie zaladowac czcionki arial.ttf!" << std::endl;
    }

    std::string options[] = { "Nowa Gra", "Wczytaj Gre", "Wyniki", "Wyjscie" };

    for (int i = 0; i < MAX_ITEMS; i++) {
        menuItems[i].setFont(font);
        menuItems[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        menuItems[i].setString(options[i]);
        menuItems[i].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_ITEMS + 1) * (i + 1)));
    }

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        window.draw(menuItems[i]);
    }
}

// Przemieszczanie siê po menu
void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_ITEMS) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}