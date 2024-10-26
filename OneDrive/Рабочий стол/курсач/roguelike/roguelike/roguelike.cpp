#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

// Класс Enemy представляет врага в игре
class Enemy {
public:
    // Конструктор, задающий начальное положение врага и его здоровье
    Enemy(float x, float y) {
        enemyShape.setSize(Vector2f(50.0f, 50.0f)); // Задаем размер врага
        enemyShape.setFillColor(Color::Blue); // Устанавливаем цвет врага
        enemyShape.setPosition(x, y); // Устанавливаем позицию врага
        health = 100; // Начальное здоровье врага

        // Инициализация полоски здоровья
        healthBar.setSize(Vector2f(50.0f, 10.0f)); // Размер полоски здоровья
        healthBar.setFillColor(Color::Red); // Цвет полоски здоровья
        healthBar.setPosition(x, y - 15); // Позиция полоски здоровья над врагом
    }

    // Возвращает форму врага
    RectangleShape getShape() const { return enemyShape; }
    // Возвращает полоску здоровья
    RectangleShape getHealthBar() const { return healthBar; }
    // Возвращает текущее здоровье врага
    int getHealth() const { return health; }
    // Метод для получения урона
    void takeDamage(int damage) { health -= damage; }

    // Проверка, жив ли враг
    bool isAlive() const { return health > 0; }

    // Обновление полоски здоровья врага в зависимости от его текущего здоровья
    void updateHealthBar() {
        healthBar.setSize(Vector2f(50.0f * (health / 100.0f), 10.0f)); // Изменяем ширину полоски
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y - 15); // Обновляем позицию
    }

private:
    RectangleShape enemyShape; // Форма врага
    RectangleShape healthBar; // Полоска здоровья врага
    int health; // Текущее здоровье врага
};

// Класс Game отвечает за основную логику игры
class Game {
public:
    // Конструктор, который инициализирует окно и игрока
    Game() {
        window.create(VideoMode(800, 600), "RPG Game"); // Создание игрового окна
        window.setFramerateLimit(60); // Установка ограничения на количество кадров

        // Настройка игрока
        player.setSize(Vector2f(50.0f, 50.0f)); // Задаем размер игрока
        player.setFillColor(Color::Green); // Устанавливаем цвет игрока
        player.setPosition(375.0f, 275.0f); // Устанавливаем позицию игрока (центр экрана)

        // Инициализация полоски здоровья игрока
        playerHealthBar.setSize(Vector2f(50.0f, 10.0f)); // Размер полоски здоровья игрока
        playerHealthBar.setFillColor(Color::Red); // Цвет полоски здоровья игрока
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 15); // Позиция над игроком

        // Создание врагов на карте
        createMap();
    }

    // Метод, запускающий главный игровой цикл
    void run() {
        while (window.isOpen()) {
            handleEvents(); // Обработка событий
            update(); // Обновление логики игры
            render(); // Отрисовка объектов на экране
        }
    }

private:
    RenderWindow window; // Главное окно игры
    RectangleShape player; // Форма игрока
    RectangleShape playerHealthBar; // Полоска здоровья игрока
    vector<unique_ptr<Enemy>> enemies; // Вектор, содержащий врагов

    // Метод для создания карты и добавления врагов
    void createMap() {
        // Добавление примера врага на карту
        enemies.push_back(make_unique<Enemy>(600.0f, 400.0f));
    }

    // Метод для обработки событий (например, нажатий клавиш)
    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); // Закрытие окна
            }
        }
    }

    // Метод для обновления состояния игры
    void update() {
        // Управление движением игрока
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -5); // Движение вверх
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, 5); // Движение вниз
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-5, 0); // Движение влево
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(5, 0); // Движение вправо
        }

        // Проверка атаки врага
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            for (auto& enemy : enemies) {
                // Проверка на столкновение с врагом
                if (player.getGlobalBounds().intersects(enemy->getShape().getGlobalBounds()) && enemy->isAlive()) {
                    enemy->takeDamage(20); // Урон врагу
                    enemy->updateHealthBar(); // Обновляем полоску здоровья врага
                    if (!enemy->isAlive()) {
                        cout << "Enemy defeated!" << endl; // Вывод сообщения о победе над врагом
                    }
                    break; // Атакуем только одного врага
                }
            }
        }

        // Обновляем позицию полоски здоровья игрока
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 15); // Перемещение полоски здоровья
    }

    // Метод для отрисовки объектов на экране
    void render() {
        window.clear(); // Очистка окна
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->getShape()); // Рисуем врагов
                window.draw(enemy->getHealthBar()); // Рисуем полоску здоровья врага
            }
        }
        window.draw(player); // Рисуем игрока
        window.draw(playerHealthBar); // Рисуем полоску здоровья игрока
        window.display(); // Отображение всего на экране
    }
};

// Точка входа в программу
int main() {
    Game game; // Создание экземпляра игры
    game.run(); // Запуск игры
    return 0; // Завершение программы
}
