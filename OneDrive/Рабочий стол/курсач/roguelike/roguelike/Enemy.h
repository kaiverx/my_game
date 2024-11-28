//Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class Enemy {
public:
    // ����������� �����
    Enemy(int gridX, int gridY, int level = 1);

    // ��������� ������� �����
    void setPosition(int gridX, int gridY);

    // ��������� ����� �����
    RectangleShape getShape() const;

    // ��������� ������� ��������
    RectangleShape getHealthBar() const;

    // ��������, ��� �� ����
    bool isAlive() const;

    // ��������� ����� �����
    void takeDamage(int damage);
    
    // ��������� ���� �����
    int getAttackPower() const;

    // ��������� �������� ������ �����
    int getLevel() const;

    void levelUp();

    // ����� ���� (A*)
    std::vector<Vector2i> findPath(const std::vector<std::vector<Tile>>& grid, Vector2i start, Vector2i goal);

private:
    int health;             // ������� �������� �����
    int maxHealth;          // ������������ �������� �����
    int attackPower;        // ���� ����� �����
    int level;              // ������� �����
    RectangleShape enemyShape; // ����� �����
    RectangleShape healthBar;  // ������� ��������

    // ����� ��� ���������� �������� �� ������ ������
    void calculateStats();
};

// ���-������� ��� Vector2i
struct Vector2iHash {
    size_t operator()(const Vector2i& v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);  // ��������������� ��� ��� x � y
    }
};

// ���������� ���������� ��������� ��� Vector2i
inline bool operator==(const Vector2i& lhs, const Vector2i& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator<(const Vector2i& lhs, const Vector2i& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

// ���������� ��������� "+" ��� Vector2i
inline Vector2i operator+(const Vector2i& lhs, const Vector2i& rhs) {
    return Vector2i(lhs.x + rhs.x, lhs.y + rhs.y);
}

#endif // ENEMY_H
