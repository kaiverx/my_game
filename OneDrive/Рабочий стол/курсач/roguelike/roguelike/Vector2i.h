#include <SFML/System/Vector2.hpp>

// Определяем оператор < для sf::Vector2i, чтобы он мог быть использован в контейнерах, требующих упорядочивания.
namespace sf {
    bool operator<(const Vector2i& lhs, const Vector2i& rhs) {
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
}