#include "Entity.h"
#include "State.h"
#include <Box2D/Box2D.h>

Entity::Entity(b2Vec2 maxVelocity) : maxVelocity(maxVelocity) {}

Player::Player(sf::Vector2f size, b2Vec2 maxVelocity, float x, float y, b2World* world) : Entity(maxVelocity) {
    shape = new sf::RectangleShape(size);
    shape->setPosition(x, y);

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(x, y);
    body = world->CreateBody(&myBodyDef);

    b2PolygonShape polygonShape;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(size.x/2, size.y/2);
    body->CreateFixture(&myFixtureDef);
}

void Player::update() {}


Ground::Ground(sf::Vector2f size, float x, float y, b2World* world) : Entity(b2Vec2(0, 0)) {
    shape = new sf::RectangleShape(size);
    shape->setPosition(x, y);

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(x, y);
    body = world->CreateBody(&myBodyDef);

    b2PolygonShape polygonShape;

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(size.x/2, size.y/2);
    body->CreateFixture(&myFixtureDef);
}
