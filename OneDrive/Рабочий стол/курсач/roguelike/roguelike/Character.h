#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::RectangleShape {
public:
    Character(int MovesPerTurn, int health, int attack, sf::Color color, int attackRangeX, int attackRangeY);

    virtual int getAttackDamage() const;  // Получение урона
    int getHealth() const;               // Получение текущего здоровья
    void setHealth(int h);               // Установка здоровья
    void takeDamage(int damage);         // Получение урона
    int getMaxHealth() const;            // Получение максимального здоровья
    bool isAlive() const;                // Проверка, жив ли персонаж

    int getMovesPerTurn() const;         // Геттер для движений
    void setMovesPerTurn(int moves);     // Сеттер для движений

    void levelUp();                      // Повышение уровня

    int getLevel() const;                // Получение уровня
    int getAttackPower() const;          // Получение силы атаки
    int getExperience() const;           // Получение опыта

    void gainExperience(int amount);     // Получение опыта

    virtual void attack() = 0;           // Виртуальная функция атаки
    virtual int getAttackRangeX() const = 0;  // Радиус атаки по X
    virtual int getAttackRangeY() const = 0;  // Радиус атаки по Y

private:
    int MovesPerTurn;       // Количество движений за ход
    int health;             // Текущее здоровье
    int maxHealth;          // Максимальное здоровье
    int attackPower;        // Сила атаки
    int level;              // Уровень персонажа
    int experience;         // Опыт персонажа
    int attackRangeX;       // Радиус атаки по X
    int attackRangeY;       // Радиус атаки по Y
    sf::RectangleShape healthBar;  // Полоска здоровья
};

#endif // CHARACTER_H
