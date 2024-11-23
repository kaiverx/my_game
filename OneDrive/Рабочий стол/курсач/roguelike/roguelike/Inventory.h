#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Weapon.h"

class Inventory {
public:
    // Добавление оружия в инвентарь
    void addWeapon(Weapon* weapon);

    // Использование первого оружия в инвентаре
    void useWeapon(Enemy& enemy, const Vector2i& position);

private:
    std::vector<Weapon*> weapons;  // Список оружий в инвентаре
};

#endif // INVENTORY_H
