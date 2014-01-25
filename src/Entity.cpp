#include "Entity.h"

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(shape->getGlobalBounds());
}

Player::Player() : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Player::Player(float x, float y) : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}

Ground::Ground() : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Ground::Ground(int x, int y) : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}
