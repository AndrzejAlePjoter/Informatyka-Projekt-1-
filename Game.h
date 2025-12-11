// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "GameState.h"

class Game {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;
    bool m_gameOver;
    int m_score;

    void initLevel();

public:
    Game();
    void reset();

    void update(float dt, float windowWidth);
    void render(sf::RenderTarget& target);

    // Metody obs³uguj¹ce zapis/odczyt
    void saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);

    bool isGameOver() const { return m_gameOver; }
    int getScore() const { return m_score; }
};