#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

class Player;
class Ground;

typedef std::list<Ground> l_Ground;

class Entity : public sf::Transformable, public sf::Drawable {
    public:
        Entity() { velocity = sf::Vector2f(0, 0); };
        virtual ~Entity() { delete shape; };
        virtual sf::FloatRect getGlobalBounds() const;
        virtual void x_movement() {};
        virtual void y_movement() {};
        virtual void x_collisions(const l_Ground&) {};
        virtual void y_collisions(const l_Ground&) {};
    protected:
        sf::Shape* shape;
        sf::Vector2f velocity;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            target.draw(*shape, states);
        }
};

class Player : public Entity {
    public:
        Player();
        Player(float x, float y);
        ~Player() {};
        
        void x_movement();
        void y_movement();
        void x_collisions(const l_Ground&);
        void y_collisions(const l_Ground&);

        sf::Clock clock;
    private:
        bool r_pressed;
        bool l_pressed;
        bool in_air;
        static const float maxY;
        static const sf::Vector2f gravity;
        static const int move_speed;
};

const float Player::maxY = 6;
const int Player::move_speed = 3;
const sf::Vector2f Player::gravity(0, 0.03);

class Marker : public Entity {
    public:
        Marker();
        Marker(float x, float y);
        ~Marker() {};
};

class Ground : public Entity {
    public:
        Ground();
        Ground(int x, int y);
        ~Ground() {};
};
