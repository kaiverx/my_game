#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class Enemy {
public:
    // Конструктор врага
    Enemy(int gridX, int gridY);

    // Установка позиции врага
    void setPosition(int gridX, int gridY);

    // Получение формы врага
    RectangleShape getShape() const;

    // Получение полоски здоровья
    RectangleShape getHealthBar() const;

    // Проверка, жив ли враг
    bool isAlive() const;

    // Нанесение урона врагу
    void takeDamage(int damage);

    // Поиск пути (A*)
    std::vector<Vector2i> findPath(const std::vector<std::vector<Tile>>& grid, Vector2i start, Vector2i goal);

private:
    int health;             // Текущее здоровье врага
    int maxHealth;          // Максимальное здоровье врага
    RectangleShape enemyShape; // Форма врага
    RectangleShape healthBar;  // Полоска здоровья
};

// Хэш-функтор для Vector2i
struct Vector2iHash {
    size_t operator()(const Vector2i& v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);  // Комбинированный хэш для x и y
    }
};

// Перегрузка операторов сравнения для Vector2i
inline bool operator==(const Vector2i& lhs, const Vector2i& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator<(const Vector2i& lhs, const Vector2i& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

// Перегрузка оператора "+" для Vector2i
inline Vector2i operator+(const Vector2i& lhs, const Vector2i& rhs) {
    return Vector2i(lhs.x + rhs.x, lhs.y + rhs.y);
}

#endif // ENEMY_H
