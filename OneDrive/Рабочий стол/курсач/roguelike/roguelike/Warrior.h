// Warrior.h
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character {
public:
    Warrior() : Character(150, 30, sf::Color::Red,1,3) {}  // ������������� ������ ����� ��� �����

    void attack() override {
        // ���������� ����� ��� ����� (��������, ���������� ����)
    }

    int getAttackRangeX() const override {
        return 1;  // ������ ��������� ����� �� X (�������������� �����)
    }

    int getAttackRangeY() const override {
        return 3;  // ������ ��������� ����� �� Y (������������ �����)
    }
};

#endif