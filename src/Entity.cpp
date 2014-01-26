#include "Entity.h"

Entity::Entity(sf::Vector2f size, sf::Vector2f maxVelocity) :
    rec(size),
    velocity(0, 0),
    maxVelocity(maxVelocity) {}

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(rec.getGlobalBounds());
}

Player::Player(sf::Vector2f size, sf::Vector2f maxVelocity) : Entity(size, maxVelocity) {}

void Player::update(float timeDelta) {}

Ground::Ground(sf::Vector2f size, sf::Vector2f maxVelocity) : Entity(size, maxVelocity) {}
