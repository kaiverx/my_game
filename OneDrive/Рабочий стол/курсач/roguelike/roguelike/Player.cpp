#include "Player.h"

// ����������� ������
Player::Player(int startX, int startY, int maxHealth, int maxActionPoints) {
    playerShape.setSize(Vector2f(50, 50));  // ������ ������
    playerShape.setFillColor(Color::Green); // ���� ������
    playerShape.setPosition(startX * 50, startY * 50);  // ��������� �������

    this->maxHealth = maxHealth;   // ������������� ������������ ��������
    this->health = maxHealth;      // ������� �������� ����� �������������
    this->maxActionPoints = maxActionPoints;  // ������������� ������������ ���� ��������
    this->actionPoints = maxActionPoints;     // ���������� ��� ���� �������� ��������
}

// ��������� ����� ������
RectangleShape Player::getShape() const {
    return playerShape;
}

// ��������� �������� �������� ������
int Player::getHealth() const {
    return health;
}

// ��������� ����� ������
void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;  // ��������, ��� �������� �� ������ �������������
}

// ��������� ������� ����� �������� ������
int Player::getActionPoints() const {
    return actionPoints;
}

// ������������� ����� ��������
void Player::useActionPoints(int points) {
    actionPoints -= points;
    if (actionPoints < 0) actionPoints = 0;  // ���� �������� �� ����� ���� ��������������
}

// ����� ������� ������
void Player::resetPosition(int x, int y) {
    playerShape.setPosition(x * 50, y * 50);  // ������������� ����� ������� ������
}

// �������� ��� �� �����
bool Player::isAlive() const {
    return health > 0;
}
