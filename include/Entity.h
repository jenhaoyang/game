#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "Globals.h"

#include <iostream>

class Ground;
class Player;

enum e_id {
    E_NULL,
    E_PLAYER,
    E_GROUND
};

// Entities are drawable objects, they have a shape,
// a velocity, and a Box2d body which can have
// any number of fixtures
//
// There may be a better way to bind shapes to fixtures, but
// right now it's simple
class Entity : public sf::Drawable {
    public:
        Entity(b2Vec2 maxVelocity);
        virtual ~Entity();
        //step function for each entity
        virtual void update() {};
        virtual e_id getID() { return id; };
        b2Body* body;
        virtual void BeginContact(Entity* entity, void* fixtureData) = 0;
        virtual void EndContact(Entity* entity, void* fixtureData) = 0;
        virtual bool checkDestroy();
        virtual void destroy() { destroyFlag = true; }
    protected:
        //shape to be drawn on the screen
        sf::Shape* shape;
        //we can only move this fast
        b2Vec2 maxVelocity;
        e_id id;
    private:
        bool destroyFlag;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            b2Vec2 pos = body->GetPosition();
            float angle = body->GetAngle() * RADTODEG;
            shape->setPosition(pos.x * PM, pos.y * PM);
            shape->setRotation(angle);
            shape->setScale(PM, PM);
            target.draw(*shape, states);
        }
};

// the player is controlled by the Player (wow, really?)
// they inherit basic Entity functions for drawing and movement
class Player : public Entity {
    public:
        Player(sf::Vector2f size, b2Vec2 maxVelocity, float x, float y, b2World* world);
        ~Player() {};
        
        void update();

        void BeginContact(Entity* entity, void* fixtureData);
        void EndContact(Entity* entity, void* fixtureData);

        void BeginContact(Ground* ground);
        void EndContact(Ground* ground);
    protected:
        int numFootContacts;
};

// the ground
// it just kinda sits there
class Ground : public Entity {
    public:
        Ground(sf::Vector2f size, float x, float y, b2World* world);
        ~Ground() {};

        void BeginContact(Entity* entity, void* fixtureData);
        void EndContact(Entity* entity, void* fixtureData);
};

class Marker : public Entity {
    public:
        Marker(float x, float y, b2World* world);
        ~Marker() {};

        void BeginContact(Entity* entity, void* fixtureData);
        void EndContact(Entity* entity, void* fixtureData);
};
