#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

// Размеры сетки
const int TILE_SIZE = 50; // Размер одной клетки
const int GRID_WIDTH = 38; // Количество клеток по ширине
const int GRID_HEIGHT = 22; // Количество клеток по высоте

// Класс Enemy представляет врага в игре
class Enemy {
public:
    Enemy(int gridX, int gridY) {
        enemyShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE)); // Задаем размер врага
        enemyShape.setFillColor(Color::Blue); // Устанавливаем цвет врага
        setPosition(gridX, gridY); // Устанавливаем позицию врага
        maxHealth = 1000; // Максимальное здоровье врага
        health = maxHealth; // Начальное здоровье врага

        // Инициализация полоски здоровья
        healthBar.setSize(Vector2f(TILE_SIZE, 10.0f)); // Размер полоски здоровья
        healthBar.setFillColor(Color::Red); // Цвет полоски здоровья
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y - 15); // Позиция полоски здоровья над врагом
    }

    // Установка позиции врага на основе координат сетки
    void setPosition(int gridX, int gridY) {
        enemyShape.setPosition(gridX * TILE_SIZE, gridY * TILE_SIZE); // Установка позиции врага на сетке
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
        // Рассчитываем ширину полоски здоровья на основе процента здоровья
        float healthPercentage = static_cast<float>(health) / maxHealth; // Процент здоровья
        healthBar.setSize(Vector2f(TILE_SIZE * healthPercentage, 10.0f)); // Изменяем ширину полоски
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y - 15); // Обновляем позицию
    }

private:
    RectangleShape enemyShape; // Форма врага
    RectangleShape healthBar; // Полоска здоровья врага
    int health; // Текущее здоровье врага
    int maxHealth; // Максимальное здоровье врага
};

// Класс Game отвечает за основную логику игры
class Game {
public:
    Game() {
        window.create(VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE), "RPG Game"); // Создание игрового окна
        window.setFramerateLimit(60); // Установка ограничения на количество кадров

        // Настройка игрока
        player.setSize(Vector2f(TILE_SIZE, TILE_SIZE)); // Задаем размер игрока
        player.setFillColor(Color::Green); // Устанавливаем цвет игрока
        player.setPosition(2 * TILE_SIZE, 2 * TILE_SIZE); // Начальная позиция игрока

        // Инициализация полоски здоровья игрока
        playerHealthBar.setSize(Vector2f(TILE_SIZE, 10.0f)); // Размер полоски здоровья игрока
        playerHealthBar.setFillColor(Color::Red); // Цвет полоски здоровья игрока
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 15); // Позиция над игроком

        // Создание врагов на карте
        createMap();
    }

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
    bool canMove = true; // Флаг для отслеживания, может ли игрок двигаться
    int playerMaxHealth = 100; // Максимальное здоровье игрока
    int playerHealth = 100; // Текущее здоровье игрока

    void createMap() {
        enemies.push_back(make_unique<Enemy>(12, 8)); // Позиция врага в клетках
    }

    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); // Закрытие окна
            }
        }
    }

    void update() {
        Vector2i moveDirection(0, 0);

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            moveDirection.y = -1; // Движение вверх
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            moveDirection.y = 1; // Движение вниз
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            moveDirection.x = -1; // Движение влево
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            moveDirection.x = 1; // Движение вправо
        }

        if (moveDirection.x != 0 || moveDirection.y != 0) {
            if (canMove) {
                int newX = (player.getPosition().x / TILE_SIZE) + moveDirection.x;
                int newY = (player.getPosition().y / TILE_SIZE) + moveDirection.y;

                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    player.setPosition(newX * TILE_SIZE, newY * TILE_SIZE);
                    canMove = false; // Блокируем дальнейшее движение
                }
            }
        }
        else {
            canMove = true; // Разрешаем движение снова
        }

        // Обновление полоски здоровья игрока
        float playerHealthPercentage = static_cast<float>(playerHealth) / playerMaxHealth;
        playerHealthBar.setSize(Vector2f(TILE_SIZE * playerHealthPercentage, 10.0f)); // Изменяем ширину полоски здоровья игрока
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 15); // Обновляем позицию полоски здоровья игрока

        // Проверка атаки врага
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            for (auto& enemy : enemies) {
                if (player.getGlobalBounds().intersects(enemy->getShape().getGlobalBounds()) && enemy->isAlive()) {
                    enemy->takeDamage(20); // Урон врагу
                    enemy->updateHealthBar(); // Обновляем полоску здоровья врага
                    if (!enemy->isAlive()) {
                        cout << "Enemy defeated!" << endl; // Вывод сообщения о победе над врагом
                        // Удаляем мертвого врага из списка (опционально)
                        enemies.erase(remove_if(enemies.begin(), enemies.end(),
                            [](const unique_ptr<Enemy>& e) { return !e->isAlive(); }),
                            enemies.end());
                    }
                    break; // Атакуем только одного врага
                }
            }
        }

        // Обновляем полоски здоровья врагов
        for (auto& enemy : enemies) {
            enemy->updateHealthBar(); // Обновляем полоски здоровья для всех врагов
        }
    }

    void render() {
        window.clear(); // Очистка окна

        // Рисуем сетку
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE)); // Создаем квадрат для клетки
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE); // Установка позиции клетки
                tile.setFillColor(Color::Transparent); // Прозрачный цвет клетки
                tile.setOutlineThickness(1); // Толщина рамки
                tile.setOutlineColor(Color::White); // Цвет рамки
                window.draw(tile); // Рисуем клетку
            }
        }

        // Рисуем врагов и их полоски здоровья
        for (auto& enemy : enemies) {
            if (enemy->isAlive()) { // Проверяем, жив ли враг
                window.draw(enemy->getShape()); // Рисуем врага
                enemy->updateHealthBar(); // Обновляем полоску здоровья
                window.draw(enemy->getHealthBar()); // Рисуем полоску здоровья
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
