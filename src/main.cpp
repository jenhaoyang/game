#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "State.h"

int main() {
    // basic setup stuff
    StateChanger::window.create(sf::VideoMode(800, 600), "Game");
    StateChanger::window.setMouseCursorVisible(false);
    StateChanger::window.setVerticalSyncEnabled(true);

    // set the state to the first area, this is a test screen
    StateChanger::set_state(STATE_TEST);
    StateChanger::change_state();

    // main game loop, states have logic and render functions
    // that direct the flow of the game
    while (StateChanger::window.isOpen()) {
        StateChanger::get_state()->logic();
        StateChanger::change_state();
        StateChanger::get_state()->render();
    }
    return 0;
}
