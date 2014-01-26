#include "Entity.h"

Entity::Entity() :
    rec(sf::Vector2f(10, 10)) {}

Entity::Entity(float x, float y) :
    rec(sf::Vector2f(x, y)) {}

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(rec.getGlobalBounds());
}

Player::Player() : Entity() {}

Player::Player(float x, float y) : Entity(x, y) {}

Ground::Ground() : Entity() {}

Ground::Ground(float x, float y) : Entity(x, y) {}
