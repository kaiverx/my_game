#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Weapon.h"

class Inventory {
public:
    // ���������� ������ � ���������
    void addWeapon(Weapon* weapon);

    // ������������� ������� ������ � ���������
    void useWeapon(Enemy& enemy, const Vector2i& position);

private:
    std::vector<Weapon*> weapons;  // ������ ������ � ���������
};

#endif // INVENTORY_H
