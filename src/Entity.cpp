#include "Entity.h"
#include <iostream>

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(shape->getGlobalBounds());
}

Player::Player() : Entity(), clock(), in_air(true), grav_velocity(0), maxY(1), gravity(0, 1) {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Player::Player(int x, int y) : Entity(), clock(), in_air(true), grav_velocity(0), maxY(1), gravity(0, 1) {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}

void Player::x_movement() {
    bool pressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!r_pressed) {
            velocity.x += move_speed;
            r_pressed = true;
            pressed = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!l_pressed) {
            velocity.x -= move_speed;
            l_pressed = true;
            pressed = true;
        }
    }
    if (!pressed) {
        if (r_pressed)
            velocity.x -= move_speed;
        if (l_pressed)
            velocity.x += move_speed;
        r_pressed = false;
        l_pressed = false;
    }
    move(velocity.x, 0);
}

void Player::y_movement() {
    if (!in_air) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            in_air = true;
            velocity.y -= 15;
        }
    } else {
        if (velocity.y < maxY) {
            velocity += gravity;
        }
    }
    move(0, velocity.y);
    std::cout << velocity.y << std::endl << in_air << std::endl;
}

void Player::x_collisions(const l_Ground& grounds) {
}

void Player::y_collisions(const l_Ground& grounds) {
    for (l_Ground::const_iterator ent = grounds.begin(); ent != grounds.end(); ent++) {
        if (getGlobalBounds().intersects(ent->getGlobalBounds())) {
            in_air = false;
            velocity.y = 0;
            break;
        }
    }
}

Ground::Ground() : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(10, 10));
}

Ground::Ground(int x, int y) : Entity() {
    shape = new sf::RectangleShape(sf::Vector2f(x, y));
}
