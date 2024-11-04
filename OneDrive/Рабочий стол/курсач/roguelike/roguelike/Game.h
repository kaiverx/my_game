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

    int playerActionPoints, enemyActionPoints;
    int maxMovesPerTurn, playerMovesLeft, enemyMovesLeft;
    bool playerTurn;

    void createMap();
    void handleEvents();
    void endTurn();
    void enemyAction();
    void updateHealthText();
    void update();
    void render();
};

#endif // GAME_H
