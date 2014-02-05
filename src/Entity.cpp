#include "Entity.h"
#include "State.h"
#include "Collision.h"
#include <iostream>

Entity::Entity(sf::Vector2f size, sf::Vector2f maxVelocity) :
    rec(size),
    velocity(0, 0),
    maxVelocity(maxVelocity) {}

sf::FloatRect Entity::getGlobalBounds() const {
    return getTransform().transformRect(rec.getGlobalBounds());
}

Player::Player(sf::Vector2f size, sf::Vector2f maxVelocity) :
    Entity(size, maxVelocity),
    r_pressed(false),
    l_pressed(false),
    in_air(true),
    speed(300),
    gravity(300)
{
    if (speed > maxVelocity.x)
        speed = maxVelocity.x;
    if (gravity > maxVelocity.y)
        gravity = maxVelocity.y;
}

void Player::update(float timeDelta) {
    true_speed = speed * timeDelta;
    true_gravity = gravity * timeDelta;
    x_update();
    y_update();
    if (maxVelocity.x != -1) {
        if (velocity.x > maxVelocity.x)
            velocity.x = maxVelocity.x;
        if (velocity.x < -maxVelocity.x)
            velocity.x = -maxVelocity.x;
    }
    if (maxVelocity.y != -1) {
        if (velocity.y > maxVelocity.y)
            velocity.y = maxVelocity.y;
        if (velocity.y < -maxVelocity.y)
            velocity.y = -maxVelocity.y;
    }
    move(velocity * timeDelta);
}

void Player::x_update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!r_pressed) {
            r_pressed = true;
            velocity.x += speed;
        }
    } else if (r_pressed) {
        r_pressed = false;
        velocity.x -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!l_pressed) {
            l_pressed = true;
            velocity.x -= speed;
        }
    } else if (l_pressed) {
        l_pressed = false;
        velocity.x += speed;
    }
}

void Player::y_update() {
    if (in_air && near_ground(*this, *StateChanger::get_state()->entity_manager.get("Ground"), true_gravity)) {
        in_air = false;
        velocity.y -= gravity;
        move(0, true_gravity);
    }
    if (in_air)
        velocity.y += gravity;
}

Ground::Ground(sf::Vector2f size, sf::Vector2f maxVelocity) : Entity(size, maxVelocity) {}
