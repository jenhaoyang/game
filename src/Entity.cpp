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

void Player::movement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(1, 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-1, 0);
    }
}
