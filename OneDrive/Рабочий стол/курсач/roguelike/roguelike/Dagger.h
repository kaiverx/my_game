#ifndef DAGGER_H
#define DAGGER_H

#include "Weapon.h"
#include <vector>

class Dagger : public Weapon {
public:
    Dagger(int damage);

    // ��������������� ������� ����� ��� �������
    void attack(Enemy& enemy, const Vector2i& position) override;

private:
    int damage; // ���� �������
};

#endif // DAGGER_H
