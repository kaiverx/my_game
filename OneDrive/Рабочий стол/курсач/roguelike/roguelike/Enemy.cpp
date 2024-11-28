#include "Vector2i.h"
#include "Enemy.h"
#include <cmath>
#include <queue>
#include <unordered_map>

// ����������� �����
Enemy::Enemy(int gridX, int gridY, int level, bool isBoss) {
    this->level = level;  // ������������� �������
    this->isBoss = isBoss;
    if (isBoss) {
        enemyShape.setSize(Vector2f(50, 50)); // ������ ����� � 4 ������
        enemyShape.setFillColor(Color::Yellow);     // ���� �����
        setPosition(gridX, gridY);            // ��������� ������� �����
        calculateStats();
    }
    else {
        enemyShape.setSize(Vector2f(50, 50)); // ������ �����
        enemyShape.setFillColor(Color::Blue); // ���� �����
        setPosition(gridX, gridY);            // ��������� ������� �����
        calculateStats();                      // ��������� �������� � ���� �����
    }
    // ��������� ������� ��������
    healthBar.setSize(Vector2f(50, 10));
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(gridX * 50, gridY * 50 + 40); // ����� ������������� �������.
}

// ����� ��� ���������� �������� � ���� ����� �� ������ ������
void Enemy::calculateStats() {
    if (isBoss) {
        maxHealth = 500 + (level - 1) * 100;  // ���� ���������� � 500 ��������, ������������� �� 100 �� �������
        attackPower = 50 + (level - 1) * 10;  // ���� �������� � 50 �����, ������������� �� 10 �� �������
    }
    else {
        maxHealth = 100 + (level - 1) * 10;   // ������� �����
        attackPower = 10 + (level - 1) * 1;
    }
    health = maxHealth;                   // ������� �������� ����� ������ ����� �������������
    float healthPercentage = static_cast<float>(health) / maxHealth;
    healthBar.setSize(Vector2f(50 * healthPercentage, 10));  // ��������������� ������������� ��������)
}

int Enemy::getLevel() const {
    return level;  // ���������� ������� ������� �����
}


void Enemy::levelUp() {
    level++;  // ����������� �������
    calculateStats();  // ������������� ��������� �����
}

// ��������� ������� �����
void Enemy::setPosition(int gridX, int gridY) {
    enemyShape.setPosition(gridX * 50, gridY * 50);
    healthBar.setPosition(enemyShape.getPosition().x, enemyShape.getPosition().y + 40);
}

// ���������� ����� �����
RectangleShape Enemy::getShape() const {
    if (this == nullptr) {  // ���� ��������� �� ������ ����� null
        throw std::runtime_error("Enemy object is not initialized!");
    }
    return enemyShape;
}

// ���������� ������� �������� �����
RectangleShape Enemy::getHealthBar() const {
    return healthBar;
}

// ��������, ��� �� ����
bool Enemy::isAlive() const {
    return health > 0;
}

// ��������� ����� �����
void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

    // ���������� ������� ��������
    float healthPercentage = static_cast<float>(health) / maxHealth;
    healthBar.setSize(Vector2f(50 * healthPercentage, 10));
}

// ����� ��� ��������� ���� �����
int Enemy::getAttackPower() const {
    return attackPower;
}

// ���������� �������������� ���������� ����������
int heuristic(const Vector2i& a, const Vector2i& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// �������� ���������� ������
bool isCellValid(const Vector2i& cell, int gridWidth, int gridHeight, const std::vector<std::vector<Tile>>& grid) {
    return cell.x >= 0 && cell.x < gridWidth && cell.y >= 0 && cell.y < gridHeight && !grid[cell.y][cell.x].isWall;
}

// ����� ���� A*
std::vector<Vector2i> Enemy::findPath(const std::vector<std::vector<Tile>>& grid, Vector2i start, Vector2i goal) {
    std::unordered_map<Vector2i, Vector2i, Vector2iHash> cameFrom;  // ������ ������
    std::unordered_map<Vector2i, int, Vector2iHash> costSoFar;      // ������� �� ����
    std::priority_queue<std::pair<int, Vector2i>, std::vector<std::pair<int, Vector2i>>, std::greater<>> frontier;

    int gridWidth = grid[0].size();
    int gridHeight = grid.size();

    // ��������� �����
    frontier.emplace(0, start);
    cameFrom[start] = start;
    costSoFar[start] = 0;

    // �������� ������ ����
    while (!frontier.empty()) {
        Vector2i current = frontier.top().second;
        frontier.pop();

        if (current == goal) break;

        // �������� �������
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

    // �������������� ����
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
