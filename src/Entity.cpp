#include "Entity.h"
#include <iostream>

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(shape->getGlobalBounds());
}

Player::Player() : Entity(), clock(), in_air(true), maxY(1), gravity(0, 1) {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Player::Player(int x, int y) : Entity(), clock(), in_air(true), maxY(1), gravity(0, 1) {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}

void Player::x_movement() {
    bool pressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!r_pressed) {
            velocity.x += 1;
            r_pressed = true;
            pressed = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!l_pressed) {
            velocity.x -= 1;
            l_pressed = true;
            pressed = true;
        }
    }
    if (!pressed) {
        if (r_pressed)
            velocity.x -= 1;
        if (l_pressed)
            velocity.x += 1;
        r_pressed = false;
        l_pressed = false;
    }
    move(velocity.x, 0);
}

void Player::y_movement() {
    if (in_air) {
        move(0, velocity.y);
        if (velocity.y < maxY)
            velocity += gravity;
    }
}

void Player::x_collisions(l_Entity col_list) {
}

void Player::y_collisions(l_Entity col_list) {
    for (l_Entity::const_iterator ent = col_list.begin(); ent != col_list.end(); ent++) {
        if (getGlobalBounds().intersects((*ent)->getGlobalBounds())) {
            Ground* g = dynamic_cast<Ground*>(*ent);
            if (g != NULL) {
                in_air = false;
            }
        }
    }

}

Ground::Ground() : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Ground::Ground(int x, int y) : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}
