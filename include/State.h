#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

enum e_State {
    STATE_NULL,
    STATE_CLOSE,
    STATE_TEST
};

class State {
    public:
        virtual ~State() {};
        virtual void logic(sf::RenderWindow& window) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
};

class StateChanger {
    public:
        StateChanger() : current_state(NULL), next_state(STATE_NULL) {};
        ~StateChanger() {};
        void set_state(e_State);
        void change_state();
        State* get_state();
    private:
        State* current_state;
        e_State next_state;
};

class MainScreen : public State {
    public:
        MainScreen();
        ~MainScreen() {};
        void logic(sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
    private:
        Player player;
        Ground ground;
        l_Ground grounds;
        l_Marker markers;
};
