#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

class Player;
class Ground;

// Entities are drawable objects, they have a shape and
// a velocity
//
// each movement direction is done before it's collsion
// this may be changed to be simpler
class Entity : public sf::Transformable, public sf::Drawable {
    public:
        virtual ~Entity() {};
        virtual sf::FloatRect getGlobalBounds() const;
    protected:
        sf::Shape* shape;
        sf::Vector2f velocity;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            target.draw(*shape, states);
        }
};

// the player is controlled by the Player (wow, really?)
// they inherit basic Entity functions for drawing and movement
class Player : public Entity {
    public:
        Player();
        Player(float x, float y);
        ~Player() {delete shape;};
};

// the ground
// it just kinda sits there
class Ground : public Entity {
    public:
        Ground();
        ~Ground() {delete shape;}
        Ground(int x, int y);
};
