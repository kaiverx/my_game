#include "Inventory.h"
#include <iostream>

void Inventory::addWeapon(Weapon* weapon) {
    weapons.push_back(weapon);
    std::cout << "Weapon added to inventory!" << std::endl;
}

void Inventory::useWeapon(Enemy& enemy, const Vector2i& position) {
    if (!weapons.empty()) {
        // Используем первое оружие в инвентаре (можно сделать выбор, но пока используем первое)
        weapons[0]->attack(enemy, position);
    }
    else {
        std::cout << "No weapons in inventory!" << std::endl;
    }
}
