#include "Dagger.h"
#include <iostream>

Dagger::Dagger(int damage) : damage(damage) {}

void Dagger::attack(Enemy& enemy, const Vector2i& position) {
    // ������, ��� ������ ������� ����� � �������� ������ (� �������� ����� ������ ����� �����).
    // �� ������� �����, ���� �� ��������� ����� ����� ���������� (��������, �� ����������� "�����").

    Vector2i attackPosition = position + Vector2i(0, -1);  // ������ ����������� (�����)

    // ���������, ��������� �� ���� � ��������� ������
    if (enemy.getShape().getGlobalBounds().intersects(Tile(attackPosition.x, attackPosition.y).shape.getGlobalBounds())) {
        // ���� � �������� ������������, ������� ����
        enemy.takeDamage(damage);
        std::cout << "Enemy hit! Damage: " << damage << std::endl;
    }
}
