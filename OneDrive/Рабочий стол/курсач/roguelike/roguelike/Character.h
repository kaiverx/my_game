#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::RectangleShape {
public:
    Character(int MovesPerTurn, int health, int attack, sf::Color color, int attackRangeX, int attackRangeY);

    virtual int getAttackDamage() const;  // ��������� �����
    int getHealth() const;               // ��������� �������� ��������
    void setHealth(int h);               // ��������� ��������
    void takeDamage(int damage);         // ��������� �����
    int getMaxHealth() const;            // ��������� ������������� ��������
    bool isAlive() const;                // ��������, ��� �� ��������

    int getMovesPerTurn() const;         // ������ ��� ��������
    void setMovesPerTurn(int moves);     // ������ ��� ��������

    void levelUp();                      // ��������� ������

    int getLevel() const;                // ��������� ������
    int getAttackPower() const;          // ��������� ���� �����
    int getExperience() const;           // ��������� �����

    void gainExperience(int amount);     // ��������� �����

    virtual void attack() = 0;           // ����������� ������� �����
    virtual int getAttackRangeX() const = 0;  // ������ ����� �� X
    virtual int getAttackRangeY() const = 0;  // ������ ����� �� Y

private:
    int MovesPerTurn;       // ���������� �������� �� ���
    int health;             // ������� ��������
    int maxHealth;          // ������������ ��������
    int attackPower;        // ���� �����
    int level;              // ������� ���������
    int experience;         // ���� ���������
    int attackRangeX;       // ������ ����� �� X
    int attackRangeY;       // ������ ����� �� Y
    sf::RectangleShape healthBar;  // ������� ��������
};

#endif // CHARACTER_H
