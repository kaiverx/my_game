// Mage.h
#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character {
public:
    Mage() : Character(100, 200, sf::Color::Blue, 3, 3) {}  // ������������� ������ ����� ��� ����

    void attack() override {
        // ���������� ����� ��� ���� (��������, ���������� ����)
    }

    int getAttackRangeX() const override {
        return 3;  // ������ ��������� ����� �� X (�������������� �����)
    }

    int getAttackRangeY() const override {
        return 3;  // ������ ��������� ����� �� Y (������������ �����)
    }
};

#endif