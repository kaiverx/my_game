#include "Dagger.h"
#include <iostream>

Dagger::Dagger(int damage) : damage(damage) {}

void Dagger::attack(Enemy& enemy, const Vector2i& position) {
    // ѕример, как кинжал атакует врага в соседней клетке (в пределах одной клетки перед собой).
    // ћы атакуем врага, если он находитс€ пр€мо перед персонажем (например, по направлению "вверх").

    Vector2i attackPosition = position + Vector2i(0, -1);  // ѕример направлени€ (вверх)

    // ѕровер€ем, находитс€ ли враг в атакуемой клетке
    if (enemy.getShape().getGlobalBounds().intersects(Tile(attackPosition.x, attackPosition.y).shape.getGlobalBounds())) {
        // ¬раг в пределах дос€гаемости, наносим урон
        enemy.takeDamage(damage);
        std::cout << "Enemy hit! Damage: " << damage << std::endl;
    }
}
