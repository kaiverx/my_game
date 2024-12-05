#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"
#include "Enemy.h"
#include "Mage.h"
#include "Warrior.h"
#include "Level.h"

using namespace sf;
using namespace std;

class Game {
public:
    Game();                    // Конструктор
    void run();                // Основной цикл игры

private:
    // Основное окно игры
    RenderWindow window;

    // Игрок и его атрибуты
    RectangleShape playerShape;  // Форма игрока
    int playerMaxHealth;         // Максимальное здоровье игрока
    int playerHealth;            // Текущее здоровье игрока
    Character* player;           // Указатель на выбранного персонажа
    Warrior warrior;             // Воин как один из персонажей
    Mage mage;                   // Маг как второй персонаж

    // Интерфейс для игрока
    CircleShape playerHealthCircle;  // Графическое представление здоровья
    Text playerHealthText;           // Текст для отображения здоровья
    Font font;                       // Шрифт для текста
    Text turnText;                   // Текст "Ваш ход"
    bool showTurnText;               // Флаг показа текста "Ваш ход"
    Clock turnTextTimer;             // Таймер для текста "Ваш ход"
    Text playerLVL;
    Text playerDMG;
    Text playerHP;
    Text enemyLVL;

    // Карта и игровые элементы
    vector<vector<Tile>> grid;       // Игровая сетка (карта)
    RectangleShape mapShape;         // Общая форма карты
    vector<shared_ptr<Enemy>> enemies; // Враги на карте
    vector<RectangleShape> healthBars; // Полоски здоровья врагов
    int playerLevel;          // Уровень игрока
    int playerAttackPower;    // Сила атаки игрока

    // Механики боя и хода
    int attackDamage;               // Урон игрока
    int playerActionPoints;         // Очки действий игрока
    int enemyActionPoints;          // Очки действий врага
    int maxMovesPerTurn;            // Максимум ходов за один ход
    int playerMovesLeft;            // Остаток ходов игрока
    int enemyMovesLeft;             // Остаток ходов врага
    bool playerTurn;                // Флаг текущего хода игрока
    bool canAttack;                 // Флаг, можно ли атаковать
    bool isPreparingAttack = false; // Состояние подготовки к атаке
    std::shared_ptr<Enemy> selectedEnemy = nullptr; // Указатель на выбранного врага
    int attackRangeX = 1;           // Радиус атаки по оси X
    int attackRangeY = 1;           // Радиус атаки по оси Y
    int attackDirectionX = 0;  // Направление по оси X (влево/вправо)
    int attackDirectionY = 0;  // Направление по оси Y (вверх/вниз)

    // Элементы интерфейса для кнопок
    CircleShape endTurnButton;      // Кнопка окончания хода
    Text endTurnButtonText;         // Текст кнопки окончания хода
    CircleShape mageButton;         // Кнопка выбора мага
    CircleShape warriorButton;      // Кнопка выбора воина
    CircleShape attackButton;       // Кнопка атаки
    Text attackButtonText;          // Текст на кнопке атаки

    // Вспомогательные флаги
    bool isAttacking;               // Флаг режима атаки
    int enemyLvlCount;
    int bossLvlCount;

    // Приватные методы
    void createMap();               // Генерация карты
    void handleEvents();            // Обработка событий
    void update();                  // Обновление игрового состояния
    void render();                  // Отрисовка элементов
    void endTurn();                 // Завершение хода игрока
    void enemyAction();             // Действия врагов
    void updateHealthText();        // Обновление текста здоровья
    void playerAttack();            // Атака игрока
    void chooseCharacter(int choice); // Выбор персонажа (1 - воин, 2 - маг)
    void highlightAttackArea();     // Подсветка области атаки
    void spawnEnemies(int count);
    void onEnemyDefeated(std::shared_ptr<Enemy>& enemy);
    void updateEnemyLvlText();

    Enemy* enemy;

    std::shared_ptr<Enemy> boss;  // Умный указатель на босса
};

#endif // GAME_H
