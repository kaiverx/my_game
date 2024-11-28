//Tile.h
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

using namespace sf;

const int TILE_SIZE = 50;
const int GRID_WIDTH = 33;
const int GRID_HEIGHT = 17;

class Tile {
public:
    RectangleShape shape;
    bool isOccupied;
    bool hasEnemy;  // �������� �� ��, ���� �� ���� �� ������
    bool isWall;
    const sf::RectangleShape& getShape() const;

    Tile();
    Tile(int x, int y);

    bool isAvailableForMove() const { // �������� �� ����������� ������ ��� ��������
        return !isWall && !hasEnemy;
    }
};
#endif // TILE_H