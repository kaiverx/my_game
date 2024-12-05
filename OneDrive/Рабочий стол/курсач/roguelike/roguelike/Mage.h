// Mage.h
#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character {
public:
    Mage() : Character(6, 100, 100, sf::Color::Red, 3, 3) {}  // ������������� ������ ����� ��� ����

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