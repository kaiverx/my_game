// Mage.h
#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character {
public:
    Mage() : Character(6, 100, 100, sf::Color::Red, 3, 3) {}  // Устанавливаем радиус атаки для мага

    void attack() override {
        // Реализация атаки для мага (например, магический урон)
    }

    int getAttackRangeX() const override {
        return 3;  // Пример диапазона атаки по X (горизонтальная линия)
    }

    int getAttackRangeY() const override {
        return 3;  // Пример диапазона атаки по Y (вертикальная линия)
    }
};

#endif