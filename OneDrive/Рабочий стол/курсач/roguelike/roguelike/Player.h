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

    // Функции перемещения
    void move(int dx, int dy, std::vector<std::vector<Tile>>& grid);

    // Функция атаки
    void attack(Player& target);

    // Функция получения урона
    void takeDamage(int damage);

    // Функция восстановления здоровья
    void heal(int amount);

    // Функция восстановления маны
    void regenerateMana(int amount);

    // Рисование игрока на экране
    void draw(RenderWindow& window);

    // Функция использования маны
    bool useMana(int amount);

    // Функция для проверки, жив ли персонаж
    bool isAlive() const;

    // Функция для установки позиции игрока
    void setPosition(int x, int y);

    // Функция для получения позиции игрока
    Vector2i getPosition() const;
};

#endif // PLAYER_H
