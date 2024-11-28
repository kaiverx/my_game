#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::RectangleShape {
public:
    Character(int health, int attack, sf::Color color, int attackRangeX, int attackRangeY);

    virtual int getAttackDamage() const;
    int getHealth() const;
    void setHealth(int h);
    void takeDamage(int damage);
    int getMaxHealth() const;
    bool isAlive() const;

    void levelUp();  // Метод повышения уровня

    int getLevel() const;
    int getAttackPower() const;
    int getExperience() const;  // Получение опыта

    void gainExperience(int amount);  // Получение опыта

    virtual void attack() = 0;
    virtual int getAttackRangeX() const = 0;
    virtual int getAttackRangeY() const = 0;

private:
    int health;
    int maxHealth;
    int attackPower;
    int level;
    int experience;  // Новый параметр - опыт игрока
    int attackRangeX;
    int attackRangeY;
    sf::RectangleShape playerShape;
    sf::RectangleShape healthBar;
};

#endif // CHARACTER_H
