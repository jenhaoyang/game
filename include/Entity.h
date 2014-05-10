#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

// Entities are drawable objects, they have a shape,
// a velocity, and a Box2d body which can have
// any number of fixtures
//
// There may be a better way to bind shapes to fixtures, but
// right now it's simple
class Entity : public sf::Drawable {
    public:
        Entity(b2Vec2 maxVelocity);
        virtual ~Entity() {};
        //step function for each entity
        virtual void update() {};
        b2Body* body;
    protected:
        //shape to be drawn on the screen
        sf::Shape* shape;
        //we can only move this fast
        b2Vec2 maxVelocity;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= shape->getTransform();
            target.draw(*shape, states);
        }
};

// the player is controlled by the Player (wow, really?)
// they inherit basic Entity functions for drawing and movement
class Player : public Entity {
    public:
        Player(sf::Vector2f size, b2Vec2 maxVelocity, float x, float y);
        ~Player() { delete shape; }
        
        void update();
};

// the ground
// it just kinda sits there
class Ground : public Entity {
    public:
        Ground(sf::Vector2f size, float x, float y);
        ~Ground() { delete shape; }
};
