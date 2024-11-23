#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Player {
public:
    Player(int startX, int startY, int maxHealth, int maxActionPoints);

    // ��������� ����� ������
    RectangleShape getShape() const;

    // ��������� �������� ������
    int getHealth() const;
    void takeDamage(int damage);

    // ��������� ����� �������� ������
    int getActionPoints() const;
    void useActionPoints(int points);

    // ������� � �������� �������
    void resetPosition(int x, int y);

    // ��������� �������� ��������� (��� ����������)
    bool isAlive() const;

private:
    RectangleShape playerShape;  // ����� ������
    int health;                  // ������� ��������
    int maxHealth;               // ������������ ��������
    int actionPoints;            // ���� ��������
    int maxActionPoints;         // ������������ ���� ��������
};

#endif // PLAYER_H
