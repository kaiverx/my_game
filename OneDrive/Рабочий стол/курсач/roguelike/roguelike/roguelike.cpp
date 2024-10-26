#include <SFML/Graphics.hpp> // Подключение библиотеки для работы с графикой
#include <vector>            // Подключение библиотеки для работы с векторами
#include <memory>            // Подключение библиотеки для работы с умными указателями
#include <iostream>          // Подключение библиотеки для работы с выводом информации

using namespace sf;
using namespace std;

// Размеры сетки и игрового поля
const int TILE_SIZE = 50;         // Размер одной клетки
const int GRID_WIDTH = 33;        // Количество клеток по ширине
const int GRID_HEIGHT = 17;       // Количество клеток по высоте

// Класс Enemy представляет врага в игре
class Enemy {
public:
    // Конструктор, инициализирующий врага на заданных координатах сетки
    Enemy(int gridX, int gridY) {
        // Создание формы врага
        enemyShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
        enemyShape.setFillColor(Color::Blue); // Установка цвета врага
        setPosition(gridX, gridY); // Установка позиции врага на сетке
        maxHealth = 100; // Установка максимального здоровья
        health = maxHealth; // Изначальное здоровье равно максимальному

        // Инициализация полоски здоровья
        healthBar.setSize(Vector2f(TILE_SIZE, 10.0f));
        healthBar.setFillColor(Color::Red);
    }

    // Метод для установки позиции врага по координатам сетки
    void setPosition(int gridX, int gridY) {
        enemyShape.setPosition(gridX * TILE_SIZE, gridY * TILE_SIZE);
        // Полоска здоровья располагается чуть ниже формы врага
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + TILE_SIZE + 5);
    }

    void moveTowardsPlayer(const RectangleShape& playerShape) {
        float playerX = playerShape.getPosition().x;
        float playerY = playerShape.getPosition().y;

        float enemyX = enemyShape.getPosition().x;
        float enemyY = enemyShape.getPosition().y;

        if (enemyX < playerX) enemyX += 1.0f; // Перемещение вправо
        if (enemyX > playerX) enemyX -= 1.0f; // Перемещение влево
        if (enemyY < playerY) enemyY += 1.0f; // Перемещение вниз
        if (enemyY > playerY) enemyY -= 1.0f; // Перемещение вверх

        enemyShape.setPosition(enemyX, enemyY); // Установка новой позиции
    }

    // Методы доступа к форме и полоске здоровья врага
    RectangleShape getShape() const { return enemyShape; }
    RectangleShape getHealthBar() const { return healthBar; }

    // Возвращает текущее здоровье врага
    int getHealth() const { return health; }

    // Метод для уменьшения здоровья врага
    void takeDamage(int damage) { health -= damage; }

    // Проверяет, жив ли враг
    bool isAlive() const { return health > 0; }

    // Обновление полоски здоровья врага
    void updateHealthBar() {
        // Вычисляем процент оставшегося здоровья
        float healthPercentage = static_cast<float>(health) / maxHealth;
        healthBar.setSize(Vector2f(TILE_SIZE * healthPercentage, 10.0f)); // Меняем ширину полоски здоровья
        healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + TILE_SIZE + 5); // Обновляем позицию полоски
    }

private:
    RectangleShape enemyShape; // Форма врага
    RectangleShape healthBar;  // Полоска здоровья врага
    int health;                // Текущее здоровье врага
    int maxHealth;             // Максимальное здоровье врага
};

// Класс Game отвечает за основную логику игры
class Game {
public:
    Game() {
        window.create(VideoMode(1920, 1080), "RPG Game"); // Создание игрового окна 1920x1080
        window.setFramerateLimit(60); // Ограничение кадров для стабильности

        // Инициализация игрока
        player.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
        player.setFillColor(Color::Green);
        player.setPosition(2 * TILE_SIZE, 2 * TILE_SIZE); // Установка начальной позиции игрока

        // Настройка круга здоровья игрока
        playerHealthCircle.setRadius(70); // Радиус круга
        playerHealthCircle.setFillColor(Color::Red);
        playerHealthCircle.setOutlineThickness(5);
        playerHealthCircle.setOutlineColor(Color::White);
        playerHealthCircle.setPosition(305, 885); // Расположение круга здоровья
        playerMaxHealth = 100;
        playerHealth = 100;

        // Загрузка шрифта для отображения текста здоровья
        if (!font.loadFromFile("Arial.ttf")) { // Проверка загрузки шрифта
            cout << "Error loading font\n";
        }

        // Настройка текста для отображения количества здоровья
        playerHealthText.setFont(font);               // Присваиваем шрифт
        playerHealthText.setCharacterSize(24);        // Размер текста
        playerHealthText.setFillColor(Color::White);  // Цвет текста
        playerHealthText.setStyle(Text::Bold);        // Стиль текста
        playerHealthText.setPosition(320, 940);       // Позиция внутри круга здоровья
        updateHealthText();                           // Устанавливаем начальное значение текста здоровья

        createMap(); // Создание начальных объектов на карте

        // Создание квадрата для карты
        mapShape.setSize(Vector2f(230, 230)); // Устанавливаем размер квадрата
        mapShape.setFillColor(Color::White);  // Устанавливаем цвет квадрата
        mapShape.setPosition(0, 850);         // Позиция квадрата (левый нижний угол)
    }

    // Запуск игры
    void run() {
        while (window.isOpen()) {
            handleEvents(); // Обработка событий
            update();       // Обновление логики
            render();       // Отрисовка объектов
        }
    }

private:
    RenderWindow window;        // Главное окно игры
    RectangleShape player;      // Форма игрока
    CircleShape playerHealthCircle; // Круг здоровья игрока
    Text playerHealthText;      // Текст для отображения здоровья игрока
    Font font;                  // Шрифт для текста
    vector<unique_ptr<Enemy>> enemies; // Контейнер для врагов
    bool canMove = true;        // Флаг для отслеживания возможности движения игрока
    int playerMaxHealth;        // Максимальное здоровье игрока
    int playerHealth;           // Текущее здоровье игрока
    RectangleShape mapShape;    // Квадрат для карты

    // Создание врагов и объектов на карте
    void createMap() {
        enemies.push_back(make_unique<Enemy>(12, 8)); // Создание врага на определенной позиции
    }

    // Обработка событий окна
    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); // Закрытие окна
            }
        }
    }

    // Обновление состояния игры
    void update() {
        Vector2i moveDirection(0, 0); // Начальное направление движения

        // Проверка нажатия клавиш для движения игрока
        if (Keyboard::isKeyPressed(Keyboard::W)) moveDirection.y = -1;
        if (Keyboard::isKeyPressed(Keyboard::S)) moveDirection.y = 1;
        if (Keyboard::isKeyPressed(Keyboard::A)) moveDirection.x = -1;
        if (Keyboard::isKeyPressed(Keyboard::D)) moveDirection.x = 1;

        // Если есть движение и игрок может двигаться
        if (moveDirection.x != 0 || moveDirection.y != 0) {
            if (canMove) {
                int newX = (player.getPosition().x / TILE_SIZE) + moveDirection.x;
                int newY = (player.getPosition().y / TILE_SIZE) + moveDirection.y;

                // Проверка границ сетки
                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    player.setPosition(newX * TILE_SIZE, newY * TILE_SIZE); // Перемещение игрока
                    canMove = false; // Запрещаем дальнейшее движение до отпускания клавиши
                }
            }
        }
        else {
            canMove = true; // Разрешаем движение снова
        }

        // Обновление масштаба круга здоровья игрока
        float playerHealthPercentage = static_cast<float>(playerHealth) / playerMaxHealth;
        playerHealthCircle.setScale(playerHealthPercentage, playerHealthPercentage);
        updateHealthText(); // Обновляем текст здоровья

        // Проверка атаки по врагам при нажатии на пробел
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            for (auto& enemy : enemies) {
                // Если враг пересекается с игроком и еще жив
                if (player.getGlobalBounds().intersects(enemy->getShape().getGlobalBounds()) && enemy->isAlive()) {
                    enemy->takeDamage(20); // Наносим урон врагу
                    enemy->updateHealthBar(); // Обновляем полоску здоровья врага
                    if (!enemy->isAlive()) {
                        cout << "Enemy defeated!" << endl; // Сообщение о смерти врага
                        // Удаление мертвого врага из списка
                        enemies.erase(remove_if(enemies.begin(), enemies.end(),
                            [](const unique_ptr<Enemy>& e) { return !e->isAlive(); }),
                            enemies.end());
                    }
                    break;
                }
            }
        }
    }

    // Обновление текста для отображения здоровья игрока
    void updateHealthText() {
        // Устанавливаем формат "Текущее Здоровье / Максимальное Здоровье"
        playerHealthText.setString(to_string(playerHealth) + " / " + to_string(playerMaxHealth));
    }


    // Отрисовка объектов на экране
     void render() {
        window.clear(); // Очистка экрана

        // Отрисовка сетки
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                tile.setFillColor(Color::Transparent);
                tile.setOutlineThickness(1);
                tile.setOutlineColor(Color::White);
                window.draw(tile);
            }
        }

        // Отрисовка врагов и их полосок здоровья
        for (auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->getShape());
                window.draw(enemy->getHealthBar());
            }
        }

        window.draw(player);               // Отрисовка игрока
        window.draw(playerHealthCircle);   // Отрисовка круга здоровья игрока
        window.draw(playerHealthText);     // Отрисовка текста количества здоровья игрока

        // Отрисовка квадрата для карты
        window.draw(mapShape); // Отрисовка квадрата карты

        window.display(); // Отображение содержимого окна
    }
};

int main() {
    Game game; // Создание объекта игры
    game.run(); // Запуск игры
    return 0; // Завершение программы
}
