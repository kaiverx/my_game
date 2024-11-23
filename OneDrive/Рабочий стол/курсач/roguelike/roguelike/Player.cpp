#include "Player.h"

// Конструктор игрока
Player::Player(int startX, int startY, int maxHealth, int maxActionPoints) {
    playerShape.setSize(Vector2f(50, 50));  // Размер игрока
    playerShape.setFillColor(Color::Green); // Цвет игрока
    playerShape.setPosition(startX * 50, startY * 50);  // Начальная позиция

    this->maxHealth = maxHealth;   // Устанавливаем максимальное здоровье
    this->health = maxHealth;      // Текущее здоровье равно максимальному
    this->maxActionPoints = maxActionPoints;  // Устанавливаем максимальные очки действия
    this->actionPoints = maxActionPoints;     // Изначально все очки действия доступны
}

// Получение формы игрока
RectangleShape Player::getShape() const {
    return playerShape;
}

// Получение текущего здоровья игрока
int Player::getHealth() const {
    return health;
}

// Нанесение урона игроку
void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;  // Убедимся, что здоровье не станет отрицательным
}

// Получение текущих очков действия игрока
int Player::getActionPoints() const {
    return actionPoints;
}

// Использование очков действия
void Player::useActionPoints(int points) {
    actionPoints -= points;
    if (actionPoints < 0) actionPoints = 0;  // Очки действия не могут быть отрицательными
}

// Сброс позиции игрока
void Player::resetPosition(int x, int y) {
    playerShape.setPosition(x * 50, y * 50);  // Устанавливаем новую позицию игрока
}

// Проверка жив ли игрок
bool Player::isAlive() const {
    return health > 0;
}
