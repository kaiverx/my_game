#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Player {
public:
    Player(int startX, int startY, int maxHealth, int maxActionPoints);

    // Получение формы игрока
    RectangleShape getShape() const;

    // Получение здоровья игрока
    int getHealth() const;
    void takeDamage(int damage);

    // Получение очков действия игрока
    int getActionPoints() const;
    void useActionPoints(int points);

    // Возврат к исходной позиции
    void resetPosition(int x, int y);

    // Получение текущего состояния (для обновлений)
    bool isAlive() const;

private:
    RectangleShape playerShape;  // Форма игрока
    int health;                  // Текущее здоровье
    int maxHealth;               // Максимальное здоровье
    int actionPoints;            // Очки действия
    int maxActionPoints;         // Максимальные очки действия
};

#endif // PLAYER_H
