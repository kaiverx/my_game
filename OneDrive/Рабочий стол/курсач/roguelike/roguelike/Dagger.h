#ifndef DAGGER_H
#define DAGGER_H

#include "Weapon.h"
#include <vector>

class Dagger : public Weapon {
public:
    Dagger(int damage);

    // Переопределение функции атаки для кинжала
    void attack(Enemy& enemy, const Vector2i& position) override;

private:
    int damage; // Урон кинжала
};

#endif // DAGGER_H
