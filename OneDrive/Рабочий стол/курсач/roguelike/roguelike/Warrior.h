// Warrior.h
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character {
public:
    Warrior() : Character(150, 30, sf::Color::Red,1,3) {}  // Устанавливаем радиус атаки для воина

    void attack() override {
        // Реализация атаки для воина (например, физический удар)
    }

    int getAttackRangeX() const override {
        return 1;  // Пример диапазона атаки по X (горизонтальная линия)
    }

    int getAttackRangeY() const override {
        return 3;  // Пример диапазона атаки по Y (вертикальная линия)
    }
};

#endif