#pragma once
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    // Pobiera dane z gry do obiektu GameState
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones);

    // Zapisuje do pliku
    bool saveToFile(const std::string& filename);

    // Wczytuje z pliku
    bool loadFromFile(const std::string& filename);

    // Aplikuje dane z GameState z powrotem do gry
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones);
};