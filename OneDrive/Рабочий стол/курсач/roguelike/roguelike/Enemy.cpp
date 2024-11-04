#include "Enemy.h"

Enemy::Enemy(int gridX, int gridY) {
    enemyShape.setSize(Vector2f(50, 50)); // TILE_SIZE
    enemyShape.setFillColor(Color::Blue);
    setPosition(gridX, gridY);
    maxHealth = 100;
    health = maxHealth;

    healthBar.setSize(Vector2f(50, 10)); // TILE_SIZE
    healthBar.setFillColor(Color::Red);
}

void Enemy::setPosition(int gridX, int gridY) {
    enemyShape.setPosition(gridX * 50, gridY * 50); // TILE_SIZE
    healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + 50 - 10); // TILE_SIZE
}

RectangleShape Enemy::getShape() const { return enemyShape; }
RectangleShape Enemy::getHealthBar() const { return healthBar; }
bool Enemy::isAlive() const { return health > 0; }
