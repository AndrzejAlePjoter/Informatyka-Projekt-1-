#include "Game.h"
#include "Global.h"
#include <iostream>

Game::Game()
    : m_paletka(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 40, 100.f, 20.f, 7.f), // Pozycja i prêdkoœæ paletki
    m_pilka(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 4.f, -4.f, 8.f), // Pozycja i prêdkoœæ pi³ki
    m_gameOver(false),
    m_score(0)
{
    initLevel();
}

void Game::initLevel() {
    m_bloki.clear();
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 5;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WINDOW_WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;

            // Warunki do kolorowania przyznawania blokom ¿ycia
            int hp = 1;
            if (y == 0) {
                hp = 3;
            }
            else if (y == 1 || y == 2) {
                hp = 2;
            }
            else {
                hp = 1;
            }
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), hp);
        }
    }
}

void Game::update(float dt, float windowWidth) {
    if (m_gameOver) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { //sterowanie na strza³kach
 
        m_paletka.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { //sterowanie na A i D
        m_paletka.moveRight();
    }
    m_paletka.clampToBounds(windowWidth);

    m_pilka.move();

    m_pilka.collideWalls(windowWidth, WINDOW_HEIGHT);

    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    // Kolizje z blokami
    sf::FloatRect ballBounds = sf::FloatRect(m_pilka.getX() - m_pilka.getRadius(),
        m_pilka.getY() - m_pilka.getRadius(),
        m_pilka.getRadius() * 2, m_pilka.getRadius() * 2);

    for (auto& blok : m_bloki) {
        if (!blok.isDestroyed() && blok.getGlobalBounds().intersects(ballBounds)) {
            blok.trafienie();
            m_pilka.bounceY(); // Odbicie
            break; // Jeden blok na klatkê
            blok.trafienie();
            m_score += 10; //punkty za trafienie bloku
        }
    }

    // Warunek przegranej
    if (m_pilka.getY() - m_pilka.getRadius() > WINDOW_HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_gameOver = true;
    }
}

void Game::render(sf::RenderTarget& target) {
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (const auto& blok : m_bloki) {
        blok.draw(target);
    }
}

// Zapis gry
void Game::saveGame(const std::string& filename) {
    GameState state;
    state.capture(m_paletka, m_pilka, m_bloki);
    state.saveToFile(filename);
}

// Wczytanie gry
bool Game::loadGame(const std::string& filename) {
    GameState state;
    if (state.loadFromFile(filename)) {
        state.apply(m_paletka, m_pilka, m_bloki);
        m_gameOver = false;
        return true;
    }
    return false;
}

// Nowa gra
void Game::reset() {
    m_gameOver = false;
    m_pilka.reset(400.f, 300.f, 4.0f, 4.0f);
    m_paletka.setPosition(400.f, 500.f);
    m_score = 0;
    initLevel();
}