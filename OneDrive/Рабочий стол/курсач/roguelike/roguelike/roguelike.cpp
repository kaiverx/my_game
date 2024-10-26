#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Game {
public:
    Game() {
        window.create(VideoMode(800, 600), "RPG Game");
        window.setFramerateLimit(60);

        // Настройка персонажа
        player.setSize(Vector2f(50.0f, 50.0f));
        player.setFillColor(Color::Green);
        player.setPosition(375.0f, 275.0f); // Центр экрана

        // Создание карты
        createMap();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    RenderWindow window;
    RectangleShape player;
    std::vector<RectangleShape> mapObjects; // Для хранения объектов карты

    void createMap() {
        // Пример объектов на карте
        RectangleShape wall(Vector2f(200.0f, 20.0f));
        wall.setFillColor(Color::Red);
        wall.setPosition(300.0f, 200.0f);
        mapObjects.push_back(wall);

        RectangleShape enemy(Vector2f(50.0f, 50.0f));
        enemy.setFillColor(Color::Blue);
        enemy.setPosition(600.0f, 400.0f);
        mapObjects.push_back(enemy);
    }

    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }

    void update() {
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -5);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, 5);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-5, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(5, 0);
        }
    }

    void render() {
        window.clear();
        for (const auto& object : mapObjects) {
            window.draw(object); // Рисуем объекты карты
        }
        window.draw(player); // Рисуем персонажа
        window.display();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
