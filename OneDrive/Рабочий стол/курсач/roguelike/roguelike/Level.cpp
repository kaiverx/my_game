// Level.cpp
#include "Level.h"
#include <iostream>

Level::Level(int levelNumber, Character* player) {
    this->levelNumber = levelNumber;
    this->player = player;
    this->playerLevel = 1;
}

void Level::startLevel() {
    // ������ ������ ������
    std::cout << "Starting Level " << levelNumber << std::endl;
    // ����� ����� �������� ������ ��� �������� ������ (��������, ���������� ������ ������� �� ������)
    levelUpEnemies(enemies);  // �������� ������� ������
}

void Level::endLevel(Character& player) {
    std::cout << "Level " << levelNumber << " completed!" << std::endl;
    levelUpPlayer(player);  // �������� player � ������� ��������� ������
    levelNumber++;  // ��������� � ���������� ������
}

void Level::levelUpPlayer(Character& player) {
    player.levelUp();  // ����������� ������� ������
    std::cout << "Player leveled up! New Level: " << player.getLevel() << std::endl;
}

void Level::levelUpEnemies(std::vector<std::shared_ptr<Enemy>>& enemies) {
    // ����������� ������� ���� ������ �� ������
    for (auto& enemy : enemies) {
        enemy->levelUp();  // ������ ���� �������� �������
        std::cout << "Enemy leveled up! New Level: " << enemy->getLevel() << std::endl;
    }
}
