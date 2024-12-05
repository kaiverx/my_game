// MainMenu.cpp
#include <SFML/Graphics.hpp>
#include "Game.h" // ������������, ��� ����� Game ��� ����������
#include <vector>
#include "MainMenu.h"
#include<iostream>

using namespace sf;

MainMenu::MainMenu() {
    window.create(VideoMode(1920, 1080), "Main Menu");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("Arial.ttf")) {
        std::cout << "Error loading font\n";
    }

    // �������� �������� ��� ����
    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cout << "Error loading background texture\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    playButtonShape.setSize(sf::Vector2f(400, 100));
    playButtonShape.setOutlineThickness(5);
    playButtonShape.setOutlineColor(Color(105, 105, 105));
    playButtonShape.setFillColor(Color(211, 211, 211)); // ���� ������
    playButtonShape.setPosition(760, 420); // ������� ������
 

    playButtonText.setFont(font);
    playButtonText.setString("PLAY");
    playButtonText.setCharacterSize(45);
    playButtonText.setStyle(Text::Bold);
    playButtonText.setFillColor(Color::White);
    playButtonText.setPosition(901, 441); // ������� ������

    liaderBoardButtonShape.setSize(sf::Vector2f(400, 100));
    liaderBoardButtonShape.setOutlineThickness(5);
    liaderBoardButtonShape.setOutlineColor(Color(105, 105, 105));
    liaderBoardButtonShape.setFillColor(Color(211, 211, 211)); // ���� ������
    liaderBoardButtonShape.setPosition(760, 545); // ������� ������

    liaderBoardButtonText.setFont(font);
    liaderBoardButtonText.setString("LIADER BOARD");
    liaderBoardButtonText.setCharacterSize(45);
    liaderBoardButtonText.setStyle(Text::Bold);
    liaderBoardButtonText.setFillColor(Color::White);
    liaderBoardButtonText.setPosition(787,566); // ������� ������

    howPlayButtonShape.setSize(sf::Vector2f(400, 100));
    howPlayButtonShape.setOutlineThickness(5);
    howPlayButtonShape.setOutlineColor(Color(105, 105, 105));
    howPlayButtonShape.setFillColor(Color(211, 211, 211)); // ���� ������
    howPlayButtonShape.setPosition(760, 670); // ������� ������

    howPlayButtonText.setFont(font);
    howPlayButtonText.setString("HOW TO PLAY");
    howPlayButtonText.setCharacterSize(45);
    howPlayButtonText.setStyle(Text::Bold);
    howPlayButtonText.setFillColor(Color::White);
    howPlayButtonText.setPosition(799, 691); // ������� ������

    exitButtonShape.setSize(sf::Vector2f(400, 100));
    exitButtonShape.setOutlineThickness(5);
    exitButtonShape.setOutlineColor(Color(105, 105, 105));
    exitButtonShape.setFillColor(Color(211, 211, 211)); // ���� ������
    exitButtonShape.setPosition(760, 795); // ������� ������

    exitButtonText.setFont(font);
    exitButtonText.setString("EXIT");
    exitButtonText.setCharacterSize(45);
    exitButtonText.setStyle(Text::Bold);
    exitButtonText.setFillColor(Color::White);
    exitButtonText.setPosition(906, 816); // ������� ������

    gameText.setFont(font);
    gameText.setString("RPG GAME");
    gameText.setCharacterSize(40);
    gameText.setStyle(Text::Bold);
    gameText.setFillColor(Color::White);
    gameText.setPosition(700, 800); // ������� ������
}
void MainMenu::runMenu() {
    while (window.isOpen()) {
        handleEvents();
        //update();
        render();
    }
}

void MainMenu::handleEvents() {
    Event event;
    Game game;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (playButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    game.run();
                }
                if (liaderBoardButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {

                }
                if (howPlayButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {

                }
                if (exitButtonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                }
            }
        }
    }
}

void MainMenu::render() {
    window.clear();
    // ��������� ����
    window.draw(backgroundSprite);
   
    window.draw(playButtonShape);
    window.draw(playButtonText);

    window.draw(liaderBoardButtonShape);
    window.draw(liaderBoardButtonText);

    window.draw(howPlayButtonShape);
    window.draw(howPlayButtonText);

    window.draw(exitButtonShape);
    window.draw(exitButtonText);
    window.display();
}
