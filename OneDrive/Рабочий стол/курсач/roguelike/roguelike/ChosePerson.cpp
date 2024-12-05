#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ChosePerson.h"
#include <iostream>

using namespace sf;
using namespace std;
ChosePerson::ChosePerson() {
    window.create(VideoMode(1920, 1080), "Choose Character");
    window.setFramerateLimit(60);

    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Error loading font\n";
    }
    if (!mageCharecterTexture.loadFromFile("mage.png")) {
        std::cout << "Error loading background texture\n";
    }
    mageCharecterSprite.setTexture(mageCharecterTexture);
    mageCharecterSprite.setPosition(75, 300);
    mageCharecterSprite.setScale(0.6, 0.6);

    if (!warriorCharecterTexture.loadFromFile("warrior.png")) {
        cout << "Error loading background texture\n";
    }
    warriorCharecterSprite.setTexture(warriorCharecterTexture);
    warriorCharecterSprite.setPosition(600, 300);
    warriorCharecterSprite.setScale(0.6, 0.6);

    if (!archerCharecterTexture.loadFromFile("archer.png")) {
        cout << "Error loading background texture\n";
    }
    archerCharecterSprite.setTexture(archerCharecterTexture);
    archerCharecterSprite.setPosition(1000, 300);
    archerCharecterSprite.setScale(0.6, 0.6);

    if (!thiefCharecterTexture.loadFromFile("thief.png")) {
        cout << "Error loading background texture\n";
    }
    thiefCharecterSprite.setTexture(thiefCharecterTexture);
    thiefCharecterSprite.setPosition(1600, 300);
    thiefCharecterSprite.setScale(0.43, 0.43);

    chooseText.setFont(font);
    chooseText.setString("CHOOSE YOUR CHARACTER");
    chooseText.setCharacterSize(46);
    chooseText.setStyle(Text::Bold);
    chooseText.setFillColor(Color::White);
    chooseText.setPosition(630, 50); // Позиция текста
}

void ChosePerson::runPerson() {
    while (window.isOpen()) {
        handleEvents();
        //update();
        render();
    }
}

void ChosePerson::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (mageCharecterSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                    Game game;
                    game.choosePerson(2);
                    game.run();

                }
                if (warriorCharecterSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                    Game game;
                    game.choosePerson(1);
                    game.run();
                }
                if (archerCharecterSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                    Game game;
                    game.choosePerson(3);
                    game.run();
                }
                if (thiefCharecterSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                    Game game;
                    game.choosePerson(4);
                    game.run();
                }
            }
        }
    }
}

void ChosePerson::render() {
    window.clear();

    window.draw(mageCharecterSprite);
    window.draw(warriorCharecterSprite);
    window.draw(archerCharecterSprite);
    window.draw(thiefCharecterSprite);

    window.draw(chooseText);
    
    window.display();
}