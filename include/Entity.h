#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable, public sf::Drawable {
    public:
        virtual ~Entity() {};
        virtual sf::FloatRect getGlobalBounds() const;
        virtual void movement() = 0;
    protected:
        sf::Shape* shape;
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
        
        void movement();
};
