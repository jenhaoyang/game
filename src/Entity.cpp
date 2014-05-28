#include "Entity.h"
#include "State.h"
#include <Box2D/Box2D.h>
#include <cstdint>

Entity::Entity(b2Vec2 maxVelocity) : maxVelocity(maxVelocity), id(E_NULL), destroyFlag(false) {}

Entity::~Entity() {
    delete shape;
}

bool Entity::checkDestroy() {
    if (destroyFlag)
        StateChanger::get_state()->world->DestroyBody(body);
    return destroyFlag;
}

Player::Player(sf::Vector2f size, b2Vec2 maxVelocity, float x, float y, b2World* world) : Entity(maxVelocity) {
    id = E_PLAYER;
    numFootContacts = 0;

    shape = new sf::RectangleShape(size);
    shape->setOrigin(size.x/2, size.y/2);
    shape->setPosition(x, y);
    shape->setFillColor(sf::Color::Red);

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(x, y);
    body = world->CreateBody(&myBodyDef);
    body->SetFixedRotation(true);

    b2PolygonShape polygonShape;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.density = 1;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(size.x/2, size.y/2);
    body->CreateFixture(&myFixtureDef);

    polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0, size.y/2), 0);
    myFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = body->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData((void*)1);

    body->SetUserData(this);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numFootContacts > 0) {
        float impulse = body->GetMass() * 2;
        body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter());
    }

    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());
}

void Player::BeginContact(Entity* entity, void* fixtureData) {
    if ((intptr_t)fixtureData == 1) {
        numFootContacts++;
        return;
    }
    switch(entity->getID()) {
        case E_GROUND:
            BeginContact(static_cast<Ground*>(entity));
        default:
            break;
    }
}

void Player::EndContact(Entity* entity, void* fixtureData) {
    if ((intptr_t)fixtureData == 1) {
        numFootContacts--;
        return;
    }
    switch(entity->getID()) {
        case E_GROUND:
            EndContact(static_cast<Ground*>(entity));
        default:
            break;
    }
}

void Player::BeginContact(Ground* ground) {}

void Player::EndContact(Ground* ground) {}


Ground::Ground(sf::Vector2f size, float x, float y, b2World* world) : Entity(b2Vec2(0, 0)) {
    id = E_GROUND;

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

    body->SetUserData(this);
}

void Ground::BeginContact(Entity* entity, void* fixtureData) {
    if ((intptr_t)fixtureData == 1) {
        std::cout << "Begin foot contact" << std::endl;
        return;
    }

    switch(entity->getID()) {
        default:
            break;
    }
}

void Ground::EndContact(Entity* entity, void* fixtureData) {
    if ((intptr_t)fixtureData == 1) {
        std::cout << "Begin foot contact" << std::endl;
        return;
    }

    switch(entity->getID()) {
        default:
            break;
    }
}
