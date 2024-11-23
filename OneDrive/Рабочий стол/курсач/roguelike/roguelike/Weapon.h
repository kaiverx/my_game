#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/System/Vector2.hpp>
#include "Enemy.h"
#include "Tile.h"

class Weapon {
public:
    virtual ~Weapon() {}

    // Виртуальная функция для атаки оружием
    virtual void attack(Enemy& enemy, const Vector2i& position) = 0;
};

#endif // WEAPON_H
