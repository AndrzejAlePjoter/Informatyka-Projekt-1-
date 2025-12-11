//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Global.h"
//#include "Game.h"
//#include "Menu.h"
//#include <fstream>
//#include <string>
//
//enum class GameStateEnum { Menu, Playing, Scores, Exiting };
//
//// Funkcja do odczytu rekordu z pliku
//int getHighScore() {
//    std::ifstream file("highscore.txt");
//    int score = 0;
//    if (file.is_open()) {
//        file >> score;
//    }
//    return score;
//}
//
//// Funkcja do zapisu nowego rekordu
//void saveHighScore(int score) {
//    std::ofstream file("highscore.txt");
//    if (file.is_open()) {
//        file << score;
//    }
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode((unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT), "Arkanoid SFML");
//    window.setFramerateLimit(60); // Wa¿ne dla sta³ej prêdkoœci
//
//    Menu menu(window.getSize().x, window.getSize().y);
//    Game game;
//
//    GameStateEnum currentState = GameStateEnum::Menu;
//
//    sf::Clock clock;
//
//    while (window.isOpen()) {
//        sf::Time dt = clock.restart();
//        sf::Event event;
//
//        //Obs³uga Zdarzeñ
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            // Obs³uga Menu
//            if (currentState == GameStateEnum::Menu) {
//                if (event.type == sf::Event::KeyPressed) {
//                    if (event.key.code == sf::Keyboard::Up) {
//                        menu.MoveUp();
//                    }
//                    if (event.key.code == sf::Keyboard::Down) {
//                        menu.MoveDown();
//                    }
//                    if (event.key.code == sf::Keyboard::Enter) {
//                        int pressed = menu.getPressedItem();
//                        if (pressed == 0) {
//                            game.reset();
//                            currentState = GameStateEnum::Playing;
//                        }
//                        else if (pressed == 1) { // Wczytaj
//                            if (game.loadGame("savegame.txt")) {
//                                currentState = GameStateEnum::Playing;
//                            }
//                            else {
//                                std::cout << "Blad wczytywania pliku!\n";
//                            }
//                        }
//                        else if (pressed == 2) { // Wczytaj
//                            if (game.loadGame("savegame.txt")) {
//                                currentState = GameStateEnum::Scores;
//                            }
//                            else if (pressed == 3) { // Wyjœcie
//                                window.close();
//                            }
//                        }
//                    }
//                }
//
//                // Obs³uga Gry (pauza, zapis, powrót do menu)
//                if (currentState == GameStateEnum::Playing) {
//                    if (event.type == sf::Event::KeyPressed) {
//                        if (event.key.code == sf::Keyboard::Escape) {
//                            currentState = GameStateEnum::Menu;
//                        }
//                        if (event.key.code == sf::Keyboard::F5) {
//                            game.saveGame("savegame.txt");
//                        }
//                    }
//                }
//            }
//
//            // Update 
//            if (currentState == GameStateEnum::Playing) {
//                game.update(dt.asSeconds(), (float)window.getSize().x);
//                if (game.isGameOver()) {
//                    int currentScore = game.getScore();
//                    int bestScore = getHighScore();
//
//                    if (currentScore > bestScore) {
//                        saveHighScore(currentScore);
//                        std::cout << "Nowy rekord: " << currentScore << "!" << std::endl;
//                    }
//
//                    // PrzejdŸ do menu albo zostañ w grze 
//                    currentState = GameStateEnum::Menu;
//                }
//
//                // Render 
//                window.clear(sf::Color(20, 20, 30));
//
//                if (currentState == GameStateEnum::Menu) {
//                    menu.draw(window);
//                }
//                else if (currentState == GameStateEnum::Playing) {
//                    game.render(window);
//                }
//                else if (currentState == GameStateEnum::Scores) {
//                    sf::Font font;
//                    if (!font.loadFromFile("arial.ttf")) return 1; // Zabezpieczenie
//
//                    // Pobieramy aktualny rekord z pliku
//                    int bestScore = getHighScore();
//
//                    sf::Text text;
//                    text.setFont(font);
//
//                    // Tworzymy napis z wstawion¹ liczb¹
//                    std::string message = "NAJLEPSZY WYNIK:\n\n      " + std::to_string(bestScore) + " pkt\n\n\n[ESC] Powrot";
//
//                    text.setString(message);
//                    text.setCharacterSize(30);
//                    text.setFillColor(sf::Color::Yellow); // Na ¿ó³to, ¿eby by³o ³adnie
//                    text.setPosition(250.f, 200.f);
//
//                    window.draw(text);
//                }
//                window.display();
//            }
//
//            return 0;
//        }
//    }
//}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.h"
#include "Game.h"
#include "Menu.h"

enum class GameStateEnum { Menu, Playing, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode((unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT), "Arkanoid SFML 2.6.2");
    window.setFramerateLimit(60); // dla sta³ej prêdkoœci

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameStateEnum currentState = GameStateEnum::Menu;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;

        // Obs³uga Zdarzeñ
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Obs³uga Menu
            if (currentState == GameStateEnum::Menu) {
                if (event.type == sf::Event::KeyPressed) { 
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.MoveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.MoveDown();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        int pressed = menu.getPressedItem();
                        if (pressed == 0) {
                            game.reset();
                            currentState = GameStateEnum::Playing;
                        }
                        else if (pressed == 1) { // Wczytaj
                            if (game.loadGame("savegame.txt")) {
                                currentState = GameStateEnum::Playing;
                            }
                            else {
                                std::cout << "Blad wczytywania pliku!\n";
                            }
                        }
                        else if (pressed == 3) { // Wyjœcie
                            window.close();
                        }
                    }
                }
            }

            // Obs³uga Gry (pauza, zapis, powrót do menu)
            if (currentState == GameStateEnum::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = GameStateEnum::Menu;
                    }
                    if (event.key.code == sf::Keyboard::F5) {
                        game.saveGame("savegame.txt");
                    }
                }
            }
        }

        //  Update 
        if (currentState == GameStateEnum::Playing) {
            // Przekazujemy dt (w sekundach) oraz szerokoœæ okna
            game.update(dt.asSeconds(), (float)window.getSize().x);
        }

        //  Render 
        window.clear(sf::Color(70, 20, 30));

        if (currentState == GameStateEnum::Menu) {
            menu.draw(window);
        }
        else if (currentState == GameStateEnum::Playing) {
            game.render(window);
        }

        window.display();
    }

    return 0;
}