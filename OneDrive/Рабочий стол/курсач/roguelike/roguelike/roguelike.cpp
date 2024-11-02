#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

const int TILE_SIZE = 50;  // Размер одной клетки
const int GRID_WIDTH = 33; // Ширина сетки в количестве клеток
const int GRID_HEIGHT = 17; // Высота сетки в количестве клеток

// Класс Tile представляет собой клетку игрового поля
class Tile {
public:
    Tile(int x, int y) : isOccupied(false), hasEnemy(false), hasPlayer(false), hasItem(false), hasObstacle(false) {
        tileShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE)); // Устанавливаем размер клетки
        tileShape.setOutlineThickness(1); // Толщина контура клетки
        tileShape.setOutlineColor(Color::White); // Цвет контура клетки
        tileShape.setFillColor(Color::Transparent); // Цвет заливки клетки (прозрачный)
        tileShape.setPosition(x * TILE_SIZE, y * TILE_SIZE); // Позиционируем клетку на поле
    }

    RectangleShape& getShape() { return tileShape; } // Возвращает ссылку на объект клетки для отрисовки

    bool isOccupied; // Флаг, указывающий, занята ли клетка
    bool hasEnemy; // Флаг, указывающий, есть ли враг на клетке
    bool hasPlayer; // Флаг, указывающий, есть ли игрок на клетке
    bool hasItem; // Флаг, указывающий, есть ли предмет на клетке
    bool hasObstacle; // Флаг, указывающий, есть ли препятствие на клетке

private:
    RectangleShape tileShape; // Графическое представление клетки
};

// Класс Enemy представляет врага
class Enemy {
public:
    Enemy(int gridX, int gridY) {
        enemyShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE)); // Устанавливаем размер врага
        enemyShape.setFillColor(Color::Blue); // Устанавливаем цвет врага
        setPosition(gridX, gridY); // Устанавливаем начальную позицию врага
        maxHealth = 100; // Задаем максимальное здоровье
        health = maxHealth; // Устанавливаем текущее здоровье

        healthBar.setSize(Vector2f(TILE_SIZE, 10.0f)); // Размер полоски здоровья
        healthBar.setFillColor(Color::Red); // Цвет полоски здоровья
    }

    void setPosition(int gridX, int gridY) {
        enemyShape.setPosition(gridX * TILE_SIZE, gridY * TILE_SIZE); // Устанавливаем позицию врага
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + TILE_SIZE + 5); // Позиция полоски здоровья
    }

    RectangleShape getShape() const { return enemyShape; } // Возвращает форму врага для отрисовки
    RectangleShape getHealthBar() const { return healthBar; } // Возвращает полоску здоровья для отрисовки
    bool isAlive() const { return health > 0; } // Проверяет, жив ли враг

private:
    RectangleShape enemyShape; // Графическое представление врага
    RectangleShape healthBar; // Полоска здоровья врага
    int health; // Текущее здоровье
    int maxHealth; // Максимальное здоровье
};

// Класс Game отвечает за весь игровой процесс
class Game {
public:
    Game() {
        window.create(VideoMode(1920, 1080), "RPG Game"); // Создаем окно игры
        window.setFramerateLimit(60); // Устанавливаем ограничение по FPS

        player.setSize(Vector2f(TILE_SIZE, TILE_SIZE)); // Устанавливаем размер игрока
        player.setFillColor(Color::Green); // Устанавливаем цвет игрока
        player.setPosition(2 * TILE_SIZE, 2 * TILE_SIZE); // Устанавливаем начальную позицию игрока

        playerHealthCircle.setRadius(70); // Радиус круга здоровья игрока
        playerHealthCircle.setFillColor(Color::Red); // Цвет круга здоровья игрока
        playerHealthCircle.setOutlineThickness(5); // Толщина контура круга здоровья
        playerHealthCircle.setOutlineColor(Color::White); // Цвет контура круга здоровья
        playerHealthCircle.setPosition(305, 885); // Позиция круга здоровья игрока
        playerMaxHealth = 100; // Максимальное здоровье игрока
        playerHealth = 100; // Текущее здоровье игрока

        // Загружаем шрифт для текста здоровья
        if (!font.loadFromFile("Arial.ttf")) {
            cout << "Error loading font\n";
        }

        playerHealthText.setFont(font); // Устанавливаем шрифт текста
        playerHealthText.setCharacterSize(24); // Устанавливаем размер текста
        playerHealthText.setFillColor(Color::White); // Цвет текста
        playerHealthText.setStyle(Text::Bold); // Стиль текста
        playerHealthText.setPosition(320, 940); // Позиция текста здоровья
        updateHealthText(); // Обновляем текст здоровья

        createMap(); // Создаем карту игрового поля

        mapShape.setSize(Vector2f(230, 230)); // Размер мини-карты
        mapShape.setFillColor(Color::White); // Цвет мини-карты
        mapShape.setPosition(0, 850); // Позиция мини-карты
    }

    void run() {
        while (window.isOpen()) {
            handleEvents(); // Обрабатываем события
            update(); // Обновляем состояние игры
            render(); // Рендерим содержимое
        }
    }

private:
    RenderWindow window; // Главное окно игры
    RectangleShape player; // Игрок в виде прямоугольника
    CircleShape playerHealthCircle; // Круг для отображения здоровья игрока
    Text playerHealthText; // Текст для отображения здоровья игрока
    Font font; // Шрифт для текста здоровья
    vector<unique_ptr<Enemy>> enemies; // Вектор врагов
    vector<vector<Tile>> grid; // Сетка клеток игрового поля
    int playerMaxHealth; // Максимальное здоровье игрока
    int playerHealth; // Текущее здоровье игрока
    RectangleShape mapShape; // Мини-карта

    void createMap() {
        grid.resize(GRID_HEIGHT, vector<Tile>(GRID_WIDTH, Tile(0, 0))); // Создаем сетку клеток
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                grid[y][x] = Tile(x, y); // Инициализируем каждую клетку сетки
            }
        }

        // Создаем врагов и помещаем их на сетку
        enemies.push_back(make_unique<Enemy>(5, 5)); // Создаем врага на клетке (5, 5)
        grid[5][5].isOccupied = true; // Устанавливаем флаг занятости клетки врагом
        grid[5][5].hasEnemy = true; // Устанавливаем флаг наличия врага
    }

    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Перемещение игрока по нажатию клавиши
            if (event.type == Event::KeyPressed) {
                int newX = player.getPosition().x / TILE_SIZE; // Текущая позиция по X
                int newY = player.getPosition().y / TILE_SIZE; // Текущая позиция по Y

                // Проверяем направление движения и обновляем позицию
                if (event.key.code == Keyboard::W && newY > 0 && !grid[newY - 1][newX].isOccupied) newY--;
                if (event.key.code == Keyboard::S && newY < GRID_HEIGHT - 1 && !grid[newY + 1][newX].isOccupied) newY++;
                if (event.key.code == Keyboard::A && newX > 0 && !grid[newY][newX - 1].isOccupied) newX--;
                if (event.key.code == Keyboard::D && newX < GRID_WIDTH - 1 && !grid[newY][newX + 1].isOccupied) newX++;

                // Обновляем позицию игрока
                player.setPosition(newX * TILE_SIZE, newY * TILE_SIZE);
            }
        }
    }

    void update() {
        updateHealthText(); // Обновляем текст здоровья
    }

    void updateHealthText() {
        playerHealthText.setString(to_string(playerHealth) + " / " + to_string(playerMaxHealth)); // Обновляем текст здоровья
    }

    void render() {
        window.clear(); // Очищаем окно

        for (auto& row : grid) {
            for (auto& tile : row) {
                window.draw(tile.getShape()); // Рисуем каждую клетку на экране
            }
        }

        // Рисуем врагов на экране
        for (auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->getShape()); // Рисуем врага
                window.draw(enemy->getHealthBar()); // Рисуем полоску здоровья врага
            }
        }

        window.draw(player); // Рисуем игрока
        window.draw(playerHealthCircle); // Рисуем круг здоровья игрока
        window.draw(playerHealthText); // Рисуем текст здоровья игрока
        window.draw(mapShape); // Рисуем мини-карту

        window.display(); // Отображаем содержимое окна
    }
};

int main() {
    Game game; // Создаем экземпляр игры
    game.run(); // Запускаем игру
    return 0; // Завершаем программу
}
