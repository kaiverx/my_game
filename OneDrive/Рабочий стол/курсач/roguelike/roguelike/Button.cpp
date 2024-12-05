// Button.cpp
#include "Button.h"
#include <vector>

Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font)
    : onClick(nullptr)
{
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setPosition(x, y);
    buttonShape.setFillColor(sf::Color::Green);

    buttonText.setFont(font);
    buttonText.setString(label);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(x + width / 2 - buttonText.getGlobalBounds().width / 2,
        y + height / 2 - buttonText.getGlobalBounds().height / 2);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isPressed(sf::Vector2i mousePos) const {
    return buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::setCallback(std::function<void()> callback) {
    onClick = callback;
}