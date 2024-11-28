// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

class Player {
public:
    RectangleShape shape;
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    int attackDamage;
    int defense;
    int movementRange;
    int actionPoints;

    Player(int health, int mana, int attackDamage, int defense, int movementRange, int actionPoints);

    // ������� �����������
    void move(int dx, int dy, std::vector<std::vector<Tile>>& grid);

    // ������� �����
    void attack(Player& target);

    // ������� ��������� �����
    void takeDamage(int damage);

    // ������� �������������� ��������
    void heal(int amount);

    // ������� �������������� ����
    void regenerateMana(int amount);

    // ��������� ������ �� ������
    void draw(RenderWindow& window);

    // ������� ������������� ����
    bool useMana(int amount);

    // ������� ��� ��������, ��� �� ��������
    bool isAlive() const;

    // ������� ��� ��������� ������� ������
    void setPosition(int x, int y);

    // ������� ��� ��������� ������� ������
    Vector2i getPosition() const;
};

#endif // PLAYER_H
