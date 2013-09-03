#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

class Ground;
class Marker;

typedef std::list<Ground> l_Ground;
typedef std::list<Marker> l_Marker;

class Entity : public sf::Transformable, public sf::Drawable {
    public:
        Entity() { velocity = sf::Vector2f(0, 0); };
        Entity(const Entity&);
        virtual ~Entity() {};
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
        Player(int x, int y);
        ~Player() { delete shape; };
        
        void marker_movement(l_Marker&);
        void x_movement();
        void y_movement();
        void x_collisions(const l_Ground&);
        void y_collisions(const l_Ground&);

        sf::Clock clock;
    private:
        bool r_pressed;
        bool l_pressed;
        bool in_air;
        float grav_velocity;
        const float maxY;
        const sf::Vector2f gravity;
        const static int move_speed = 3;
};

class Marker : public Entity {
    public:
        Marker();
        Marker(int x, int y);
        Marker(sf::FloatRect);
        ~Marker() { delete shape; };

        void x_movement() {};
        void y_movement() {};
        void x_collisions(const l_Ground&) {};
        void y_collisions(const l_Ground&) {};
};

class Ground : public Entity {
    public:
        Ground();
        Ground(int x, int y);
        ~Ground() { delete shape; };
};
