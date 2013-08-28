#include "Entity.h"

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(shape->getGlobalBounds());
}

Player::Player() {
    shape = new sf::RectangleShape(sf::Vector2f(0, 0));
}

Player::Player(int x, int y) {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}

void Player::x_movement(const sf::RenderWindow& window) {

}
