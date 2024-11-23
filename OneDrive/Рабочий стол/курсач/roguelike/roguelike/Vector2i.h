#include <SFML/System/Vector2.hpp>

// ���������� �������� < ��� sf::Vector2i, ����� �� ��� ���� ����������� � �����������, ��������� ��������������.
namespace sf {
    bool operator<(const Vector2i& lhs, const Vector2i& rhs) {
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
}