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
    Game();                    // �����������
    void run();                // �������� ���� ����

private:
    // �������� ���� ����
    RenderWindow window;

    // ����� � ��� ��������
    RectangleShape playerShape;  // ����� ������
    int playerMaxHealth;         // ������������ �������� ������
    int playerHealth;            // ������� �������� ������
    Character* player;           // ��������� �� ���������� ���������
    Warrior warrior;             // ���� ��� ���� �� ����������
    Mage mage;                   // ��� ��� ������ ��������

    // ��������� ��� ������
    CircleShape playerHealthCircle;  // ����������� ������������� ��������
    Text playerHealthText;           // ����� ��� ����������� ��������
    Font font;                       // ����� ��� ������
    Text turnText;                   // ����� "��� ���"
    bool showTurnText;               // ���� ������ ������ "��� ���"
    Clock turnTextTimer;             // ������ ��� ������ "��� ���"
    Text playerLVL;
    Text playerDMG;
    Text playerHP;
    Text enemyLVL;

    // ����� � ������� ��������
    vector<vector<Tile>> grid;       // ������� ����� (�����)
    RectangleShape mapShape;         // ����� ����� �����
    vector<shared_ptr<Enemy>> enemies; // ����� �� �����
    vector<RectangleShape> healthBars; // ������� �������� ������
    int playerLevel;          // ������� ������
    int playerAttackPower;    // ���� ����� ������

    // �������� ��� � ����
    int attackDamage;               // ���� ������
    int playerActionPoints;         // ���� �������� ������
    int enemyActionPoints;          // ���� �������� �����
    int maxMovesPerTurn;            // �������� ����� �� ���� ���
    int playerMovesLeft;            // ������� ����� ������
    int enemyMovesLeft;             // ������� ����� �����
    bool playerTurn;                // ���� �������� ���� ������
    bool canAttack;                 // ����, ����� �� ���������
    bool isPreparingAttack = false; // ��������� ���������� � �����
    std::shared_ptr<Enemy> selectedEnemy = nullptr; // ��������� �� ���������� �����
    int attackRangeX = 1;           // ������ ����� �� ��� X
    int attackRangeY = 1;           // ������ ����� �� ��� Y
    int attackDirectionX = 0;  // ����������� �� ��� X (�����/������)
    int attackDirectionY = 0;  // ����������� �� ��� Y (�����/����)

    // �������� ���������� ��� ������
    CircleShape endTurnButton;      // ������ ��������� ����
    Text endTurnButtonText;         // ����� ������ ��������� ����
    CircleShape mageButton;         // ������ ������ ����
    CircleShape warriorButton;      // ������ ������ �����
    CircleShape attackButton;       // ������ �����
    Text attackButtonText;          // ����� �� ������ �����

    // ��������������� �����
    bool isAttacking;               // ���� ������ �����
    int enemyLvlCount;
    int bossLvlCount;

    // ��������� ������
    void createMap();               // ��������� �����
    void handleEvents();            // ��������� �������
    void update();                  // ���������� �������� ���������
    void render();                  // ��������� ���������
    void endTurn();                 // ���������� ���� ������
    void enemyAction();             // �������� ������
    void updateHealthText();        // ���������� ������ ��������
    void playerAttack();            // ����� ������
    void chooseCharacter(int choice); // ����� ��������� (1 - ����, 2 - ���)
    void highlightAttackArea();     // ��������� ������� �����
    void spawnEnemies(int count);
    void onEnemyDefeated(std::shared_ptr<Enemy>& enemy);
    void updateEnemyLvlText();

    Enemy* enemy;

    std::shared_ptr<Enemy> boss;  // ����� ��������� �� �����
};

#endif // GAME_H
