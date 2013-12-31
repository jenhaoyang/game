#include "State.h"
#include <vector>
#include <iostream>

void StateChanger::set_state(e_State state) {
    if (next_state != STATE_CLOSE)
        next_state = state;
}

void StateChanger::change_state() {
    if (next_state != STATE_NULL) {
        delete current_state;
        switch (next_state) {
            case STATE_NULL:
                break;
            case STATE_CLOSE:
                current_state = new Closing();
            case STATE_TEST:
                current_state = new MainScreen();
                break;
        }
        next_state = STATE_NULL;
    }
}

State* StateChanger::get_state() {
    return current_state;
}

MainScreen::MainScreen() : player(50, 50), ground(800, 40) {
    ground.setPosition(0, 560);
    grounds.push_back(ground);
}

void MainScreen::logic(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            StateChanger::set_state(STATE_CLOSE);
    }
    if (player.clock.getElapsedTime().asMilliseconds() > 5) {
        player.clock.restart();
        player.x_movement();
        player.x_collisions(grounds);
        player.y_movement();
        player.y_collisions(grounds);
    }
}

void MainScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(player);
    window.draw(ground);
    window.display();
}

State* StateChanger::current_state(NULL);
e_State StateChanger::next_state = STATE_NULL;
