#pragma once
#include <SFML/Graphics.hpp>

enum e_State {
    STATE_NULL,
    STATE_TEST
};

class State {
    public:
        virtual ~State();
        virtual void logic(sf::RenderWindow& window) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
};

class MainScreen : public State {
    public:
        MainScreen();
        void logic(sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
};

class StateChanger {
    public:
        StateChanger();
        ~StateChanger();
        void changeState(e_State);
        void update_state();

        State* current_state;
};

