#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isPressed(sf::Vector2i mousePos) const;
    void setCallback(std::function<void()> callback);

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> onClick;
};
