// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

class Game {
public:
    Game();
    void run();

private:
    RenderWindow window;
    RectangleShape player;
    CircleShape playerHealthCircle;
    Text playerHealthText;
    Font font;
    int playerMaxHealth, playerHealth;
    vector<vector<Tile>> grid;
    vector<shared_ptr<Enemy>> enemies;
    RectangleShape mapShape;

    CircleShape endTurnButton;
    Text endTurnButtonText;

    int attackDamage;  // Урон, наносимый игроком
    int playerActionPoints, enemyActionPoints;
    int maxMovesPerTurn, playerMovesLeft, enemyMovesLeft;
    bool playerTurn;
    bool canAttack;  // Флаг для отслеживания, может ли игрок атаковать

    void createMap();
    void handleEvents();
    void endTurn();
    void enemyAction();
    void updateHealthText();
    void update();
    void render();
    void playerAttack();  // Функция для атаки игрока

    Text turnText; // Текст для отображения "Ваш ход"
    bool showTurnText; // Флаг для управления видимостью текста
    Clock turnTextTimer; // Таймер для отсчета времени отображения текста

    bool isAttacking;  // Флаг для определения, активен ли режим атаки
    CircleShape attackButton;  // Кнопка для активации атаки
    Text attackButtonText;  // Текст на кнопке для атаки

    vector<RectangleShape> healthBars;  // Для хранения полосок здоровья врагов

    // Новые функции
    
};

#endif // GAME_H
