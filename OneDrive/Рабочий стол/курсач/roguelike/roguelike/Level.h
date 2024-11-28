// Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Character.h"
#include "Enemy.h"

class Level {
public:
    Level(int levelNumber, Character* player);
    void startLevel();
    void endLevel(Character& player);
    void levelUpPlayer(Character& player);
    void levelUpEnemies(std::vector<std::shared_ptr<Enemy>>& enemies);

private:
    int levelNumber;
    int playerLevel;
    Character* player;
    std::vector<std::shared_ptr<Enemy>> enemies;  // Добавляем enemies как член класса
};


#endif // LEVEL_H