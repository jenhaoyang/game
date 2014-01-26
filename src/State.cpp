#include "State.h"
#include <vector>
#include <iostream>

// set what the state will change to next (can be called from
// anywhere)
void StateChanger::set_state(e_State state) {
    if (next_state != STATE_CLOSE)
        next_state = state;
}

// do the actual state change
// the current state will be set to a new state object
// and the old one will be deleted
void StateChanger::change_state() {
    if (next_state != STATE_NULL) {
        delete current_state;
        switch (next_state) {
            case STATE_NULL:
                break;
            case STATE_CLOSE:
                current_state = new Closing();
                break;
            case STATE_TEST:
                current_state = new MainScreen();
                break;
        }
        next_state = STATE_NULL;
    }
}

// the current state should be read only
State* StateChanger::get_state() {
    return current_state;
}

// this is a test area
// it contains the ground and a player
MainScreen::MainScreen() : entity_manager() {
    Player* player = new Player(50, 50);
    Ground* ground = new Ground(800, 40);
    player->setPosition(0, 0);
    ground->setPosition(0, 560);
    entity_manager.add("Player", player);
    entity_manager.add("Ground", ground);
}

// check events and do movement
// basically anything that isn't rendering
void MainScreen::logic(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            StateChanger::set_state(STATE_CLOSE);
    }
}

// draw all objects to the screen
void MainScreen::render(sf::RenderWindow& window) {
    window.clear();
    entity_manager.render(window);
    window.display();
}

// the initial state is NULL
State* StateChanger::current_state = NULL;
e_State StateChanger::next_state = STATE_NULL;
