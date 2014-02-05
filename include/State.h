#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

// available states
// NULL is no change
// CLOSE is window closing
// TEST is a test area for MainScreen
enum e_State {
    STATE_NULL,
    STATE_CLOSE,
    STATE_TEST
};

// Abstract class that defines implementation for other states
class State {
    public:
        State() : entity_manager() {}
        virtual ~State() {};
        virtual void logic(sf::RenderWindow& window) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        EntityManager entity_manager;
};

// change states
class StateChanger {
    public:
        static void set_state(e_State);
        static void change_state();
        static State* get_state();
    private:
        static State* current_state;
        static e_State next_state;
};

// test area
class MainScreen : public State {
    public:
        MainScreen();
        ~MainScreen() {};
        void logic(sf::RenderWindow& window);
        void render(sf::RenderWindow& window);
};

// The window is closing, used for cleanup
class Closing : public State {
    public:
        Closing() {};
        ~Closing() {};
        void logic(sf::RenderWindow& window) { window.close(); }
        void render(sf::RenderWindow& window) { window.close(); };
};
