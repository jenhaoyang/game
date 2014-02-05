#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// Entities are drawable objects, they have a shape and
// a velocity
//
// each movement direction is done before it's collsion
// this may be changed to be simpler
class Entity : public sf::Transformable, public sf::Drawable {
    public:
        Entity(sf::Vector2f size, sf::Vector2f maxVelocity);
        virtual ~Entity() {};
        virtual sf::FloatRect getGlobalBounds() const;
        virtual void update(float timeDelta) { move(velocity * timeDelta); };
    protected:
        sf::RectangleShape rec;
        sf::Vector2f velocity;
        sf::Vector2f maxVelocity;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            target.draw(rec, states);
        }
};

// the player is controlled by the Player (wow, really?)
// they inherit basic Entity functions for drawing and movement
class Player : public Entity {
    public:
        Player(sf::Vector2f size, sf::Vector2f maxVelocity);
        
        void update(float timeDelta);
    private:
        void x_update();
        void y_update();

        bool r_pressed;
        bool l_pressed;
        bool in_air;
        float speed;
        float gravity;
        float true_speed;
        float true_gravity;
};

// the ground
// it just kinda sits there
class Ground : public Entity {
    public:
        Ground(sf::Vector2f size, sf::Vector2f maxVelocity);
};
