#include "Vector2i.h"
#include "Enemy.h"
#include <cmath>
#include <queue>
#include <unordered_map>

// Конструктор врага
Enemy::Enemy(int gridX, int gridY) {
    enemyShape.setSize(Vector2f(50, 50)); // Размер врага
    enemyShape.setFillColor(Color::Blue); // Цвет врага
    setPosition(gridX, gridY);            // Установка позиции врага
    maxHealth = 100;                      // Максимальное здоровье
    health = maxHealth;                   // Текущее здоровье

    // Настройка полоски здоровья
    healthBar.setSize(Vector2f(50, 10));
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(gridX * 50, gridY * 50 + 40); // Сразу устанавливаем позицию.
}

// Установка позиции врага
void Enemy::setPosition(int gridX, int gridY) {
    enemyShape.setPosition(gridX * 50, gridY * 50);
    healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + 40);
}

// Возвращает форму врага
RectangleShape Enemy::getShape() const {
    return enemyShape;
}

// Возвращает полоску здоровья врага
RectangleShape Enemy::getHealthBar() const {
    return healthBar;
}

// Проверка, жив ли враг
bool Enemy::isAlive() const {
    return health > 0;
}

// Нанесение урона
void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

    // Обновление полоски здоровья
    float healthPercentage = static_cast<float>(health) / maxHealth;
    healthBar.setSize(Vector2f(50 * healthPercentage, 10));
}

// Вычисление эвристического расстояния Манхэттена
int heuristic(const Vector2i& a, const Vector2i& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Проверка валидности ячейки
bool isCellValid(const Vector2i& cell, int gridWidth, int gridHeight, const std::vector<std::vector<Tile>>& grid) {
    return cell.x >= 0 && cell.x < gridWidth && cell.y >= 0 && cell.y < gridHeight && !grid[cell.y][cell.x].isWall;
}

// Поиск пути A*
std::vector<Vector2i> Enemy::findPath(const std::vector<std::vector<Tile>>& grid, Vector2i start, Vector2i goal) {
    std::unordered_map<Vector2i, Vector2i, Vector2iHash> cameFrom;  // Откуда пришли
    std::unordered_map<Vector2i, int, Vector2iHash> costSoFar;      // Затраты на путь
    std::priority_queue<std::pair<int, Vector2i>, std::vector<std::pair<int, Vector2i>>, std::greater<>> frontier;

    int gridWidth = grid[0].size();
    int gridHeight = grid.size();

    // Начальная точка
    frontier.emplace(0, start);
    cameFrom[start] = start;
    costSoFar[start] = 0;

    // Алгоритм поиска пути
    while (!frontier.empty()) {
        Vector2i current = frontier.top().second;
        frontier.pop();

        if (current == goal) break;

        // Проверка соседей
        for (const Vector2i& dir : { Vector2i{1, 0}, Vector2i{-1, 0}, Vector2i{0, 1}, Vector2i{0, -1} }) {
            Vector2i next = current + dir;

            if (isCellValid(next, gridWidth, gridHeight, grid)) {
                int newCost = costSoFar[current] + 1;

                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    int priority = newCost + heuristic(next, goal);
                    frontier.emplace(priority, next);
                    cameFrom[next] = current;
                }
            }
        }
    }

    // Восстановление пути
    std::vector<Vector2i> path;
    Vector2i step = goal;
    if (cameFrom.find(goal) != cameFrom.end()) {
        while (step != start) {
            path.push_back(step);
            step = cameFrom[step];
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}
