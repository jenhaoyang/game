#include "Entity.h"
#include "State.h"
#include <Box2D/Box2D.h>

Entity::Entity(b2Vec2 maxVelocity) : maxVelocity(maxVelocity) {}

Player::Player(sf::Vector2f size, b2Vec2 maxVelocity, float x, float y, b2World* world) : Entity(maxVelocity) {
    shape = new sf::RectangleShape(size);
    shape->setOrigin(size.x/2, size.y/2);
    shape->setPosition(x, y);
    shape->setFillColor(sf::Color::Red);

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(x, y);
    body = world->CreateBody(&myBodyDef);

    b2PolygonShape polygonShape;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.density = 1;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(size.x/2, size.y/2);
    body->CreateFixture(&myFixtureDef);
}

void Player::update() {
    b2Vec2 vel = body->GetLinearVelocity();
    float force = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (vel.x > -5)
            force = -50;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (vel.x < 5)
            force = 50;
    } else
        force = vel.x * -10;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        float impulse = body->GetMass();
        body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter());
    }

    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());

}


Ground::Ground(sf::Vector2f size, float x, float y, b2World* world) : Entity(b2Vec2(0, 0)) {
    shape = new sf::RectangleShape(size);
    shape->setOrigin(size.x/2, size.y/2);
    shape->setPosition(x, y);
    shape->setFillColor(sf::Color::Green);

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(x, y);
    body = world->CreateBody(&myBodyDef);

    b2PolygonShape polygonShape;

    b2FixtureDef myFixtureDef;
    myFixtureDef.density = 1;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(size.x/2, size.y/2);
    body->CreateFixture(&myFixtureDef);
}
