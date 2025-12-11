#include "GameState.h"
#include <fstream>
#include <iostream>
#include "Global.h" // dla wymiarów bloków przy odtwarzaniu

// Pobranie stanu gry
void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones) {
    paddlePosition = { p.getX(), p.getY() };
    ballPosition = { b.getX(), b.getY() };
    ballVelocity = { b.getVx(), b.getVy() };

    blocks.clear();
    for (const auto& s : stones) {
        if (!s.isDestroyed()) {
            blocks.push_back({ s.getPosition().x, s.getPosition().y, s.getHP() });
        }
    }
}

// Zapisanie do pliku
bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS " << blocks.size() << "\n";

    for (const auto& b : blocks) {
        file << b.x << " " << b.y << " " << b.hp << "\n";
    }

    file.close();
    std::cout << "Gra zapisana!\n";
    return true;
}

// Wczytanie z pliku
bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;

    int count;
    if (!(file >> label >> count)) return false;

    blocks.clear();
    for (int i = 0; i < count; ++i) {
        float bx, by;
        int hp;
        file >> bx >> by >> hp;
        blocks.push_back({ bx, by, hp });
    }

    file.close();
    std::cout << "Gra wczytana!\n";
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones) {
    p.setPosition(paddlePosition.x, paddlePosition.y);
    b.reset(ballPosition.x, ballPosition.y, ballVelocity.x, ballVelocity.y);

    stones.clear();
    // Sta³e potrzebne do odtworzenia geometrii
    const int ILOSC_KOLUMN = 6;
    const float ROZMIAR_BLOKU_X = (WINDOW_WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    const float ROZMIAR_BLOKU_Y = 25.f;

    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), data.hp);
    }
}