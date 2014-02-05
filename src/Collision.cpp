#include "Collision.h"

bool near_ground(const Entity& ent1, const Entity& ent2, float distance) {
    sf::FloatRect ent1bounds = ent1.getGlobalBounds();
    sf::FloatRect ent2bounds = ent2.getGlobalBounds();
    ent1bounds.height += distance;
    return ent1bounds.intersects(ent2bounds);
}
