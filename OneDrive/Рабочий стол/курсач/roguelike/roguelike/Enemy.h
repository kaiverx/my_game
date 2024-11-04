#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy {
public:
    Enemy(int gridX, int gridY);
    void setPosition(int gridX, int gridY);
    RectangleShape getShape() const;
    RectangleShape getHealthBar() const;
    bool isAlive() const;

    int health, maxHealth;
    RectangleShape enemyShape;
    RectangleShape healthBar;
};

#endif // ENEMY_H
