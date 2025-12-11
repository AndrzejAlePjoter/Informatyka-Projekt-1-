#include "Stone.h"

// Definicja tablicy kolorów (i tak coœ nie dzia³a)
const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, // 0 HP
    sf::Color::Red,         // 1 HP
    sf::Color::Yellow,      // 2 HP
    sf::Color::Blue         // 3 HP
};

// Ustawienia bloków
Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
    : m_punktyZycia(L), m_jestZniszczony(false)
{
    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOutlineThickness(1.f);
    this->setOutlineColor(sf::Color::Black);
    aktualizujKolor();
}

void Stone::trafienie() {
    if (m_jestZniszczony) return;

    m_punktyZycia--;
    aktualizujKolor();

    if (m_punktyZycia <= 0) {
        m_jestZniszczony = true;
    }
}

void Stone::aktualizujKolor() {
    const sf::Color kolory[] = { // Tablica kolorów w funkcji, bo tamta nie dzia³a
    sf::Color::Transparent, // 0 HP
    sf::Color::Red,         // 1 HP
    sf::Color::Yellow,      // 2 HP
    sf::Color::Blue         // 3 HP
    };
    if (m_punktyZycia >= 0 && m_punktyZycia < m_colorLUT.size()) {
        this->setFillColor(kolory[m_punktyZycia]);
    }
}

void Stone::draw(sf::RenderTarget& target) const {
    if (!m_jestZniszczony) {
        target.draw(*this);
    }
}