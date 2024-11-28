// Level.cpp
#include "Level.h"
#include <iostream>

Level::Level(int levelNumber, Character* player) {
    this->levelNumber = levelNumber;
    this->player = player;
    this->playerLevel = 1;
}

void Level::startLevel() {
    // Логика начала уровня
    std::cout << "Starting Level " << levelNumber << std::endl;
    // Здесь можно добавить врагов для текущего уровня (например, количество врагов зависит от уровня)
    levelUpEnemies(enemies);  // Повышаем уровень врагов
}

void Level::endLevel(Character& player) {
    std::cout << "Level " << levelNumber << " completed!" << std::endl;
    levelUpPlayer(player);  // Передаем player в функцию повышения уровня
    levelNumber++;  // Переходим к следующему уровню
}

void Level::levelUpPlayer(Character& player) {
    player.levelUp();  // Увеличиваем уровень игрока
    std::cout << "Player leveled up! New Level: " << player.getLevel() << std::endl;
}

void Level::levelUpEnemies(std::vector<std::shared_ptr<Enemy>>& enemies) {
    // Увеличиваем уровень всех врагов на уровне
    for (auto& enemy : enemies) {
        enemy->levelUp();  // Каждый враг повышает уровень
        std::cout << "Enemy leveled up! New Level: " << enemy->getLevel() << std::endl;
    }
}
