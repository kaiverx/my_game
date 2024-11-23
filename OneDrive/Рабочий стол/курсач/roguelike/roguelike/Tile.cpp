#include "Tile.h"

// Конструктор по умолчанию
Tile::Tile() : isOccupied(false), hasEnemy(false), isWall(false) {
    shape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
}

// Конструктор с параметрами
Tile::Tile(int x, int y) : isOccupied(false), hasEnemy(false), isWall(false) {
    shape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);

    // Создание стен по краям сетки и в центре
    if (x == 0 || x == GRID_WIDTH - 1 || y == 0 || y == GRID_HEIGHT - 1) {
        isWall = true;
        shape.setFillColor(Color(139, 69, 19));
        isOccupied = true;
    }
    else if ((x >= GRID_WIDTH / 2 - 1 && x <= GRID_WIDTH / 2 + 1) &&
        (y >= GRID_HEIGHT / 2 - 1 && y <= GRID_HEIGHT / 2 + 1)) {
        isWall = true;
        shape.setFillColor(Color(150, 150, 150));
        isOccupied = true;
    }
    else {
        shape.setFillColor(Color(0, 128, 0));
    }

    shape.setOutlineThickness(1);
    shape.setOutlineColor(Color::Black);
}