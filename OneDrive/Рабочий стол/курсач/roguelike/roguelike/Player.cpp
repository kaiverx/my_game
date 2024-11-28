// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player(int health, int mana, int attackDamage, int defense, int movementRange, int actionPoints)
    : health(health), maxHealth(health), mana(mana), maxMana(mana),
    attackDamage(attackDamage), defense(defense), movementRange(movementRange), actionPoints(actionPoints) {
    shape.setSize(Vector2f(50, 50));  // ������ ������
    shape.setFillColor(Color::Green); // ���� ������ (����� �������� � ����������� �� ���� ���������)
}

void Player::move(int dx, int dy, std::vector<std::vector<Tile>>& grid) {
    // ������ ��� ����������� �� �����
    // �������� ����������� ������ ��� ��������
    int newX = shape.getPosition().x / 50 + dx;
    int newY = shape.getPosition().y / 50 + dy;

    if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT && !grid[newY][newX].isOccupied) {
        shape.setPosition(newX * 50, newY * 50);
    }
}

void Player::attack(Player& target) {
    // ������ ��� ����� ������� ������
    int damageDealt = attackDamage - target.defense;
    if (damageDealt > 0) {
        target.takeDamage(damageDealt);
    }
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Player::regenerateMana(int amount) {
    mana += amount;
    if (mana > maxMana) mana = maxMana;
}

void Player::draw(RenderWindow& window) {
    window.draw(shape);
}

bool Player::useMana(int amount) {
    if (mana >= amount) {
        mana -= amount;
        return true;
    }
    return false;
}

bool Player::isAlive() const {
    return health > 0;
}

void Player::setPosition(int x, int y) {
    shape.setPosition(x * 50, y * 50);
}

Vector2i Player::getPosition() const {
    return Vector2i(shape.getPosition().x / 50, shape.getPosition().y / 50);
}
