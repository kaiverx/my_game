#include "Character.h"

Character::Character(int health, int attack, sf::Color color, int attackRangeX, int attackRangeY)
    : health(health), maxHealth(health), attackPower(attack), attackRangeX(attackRangeX), attackRangeY(attackRangeY), level(1), experience(0) {
    setSize(sf::Vector2f(50, 50));  // ������ ���������
    setFillColor(color);  // ������������� ����
}

int Character::getAttackDamage() const {
    return attackPower;
}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int h) {
    health = h;
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

bool Character::isAlive() const {
    return health > 0;
}

// ����� ��� ��������� ������ ���������
void Character::levelUp() {
    level++;  // ����������� �������
    maxHealth += 20;  // ����������� ������������ ��������
    attackPower += 10;  // ����������� ���� �����

    health = maxHealth;  // ��������������� �������� �� ���������

    // ��������� ������� ��������
    float healthPercentage = static_cast<float>(health) / maxHealth;
    healthBar.setSize(sf::Vector2f(50 * healthPercentage, 10));
}

int Character::getLevel() const {
    return level;
}

int Character::getAttackPower() const {
    return attackPower;
}

void Character::gainExperience(int amount) {
    experience += amount;
    int experienceForLevelUp = 100 * level;  // ��������� ������� ��� XP
    if (experience >= experienceForLevelUp) {
        experience -= experienceForLevelUp;  // �������� ����, ����������� �� ��������� ������
        levelUp();  // �������� �������
    }
}

int Character::getExperience() const {
    return experience;
}
