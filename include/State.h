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
        static void set_state(e_State);
        static void change_state();
        static State* get_state();
    private:
        static State* current_state;
        static e_State next_state;
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
};

class Closing : public State {
    public:
        Closing() {};
        ~Closing() {};
        void logic(sf::RenderWindow& window) { window.close(); }
        void render(sf::RenderWindow& window) { window.close(); };
};
