#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "State.h"

int main() {
    // basic setup stuff
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    // set the state to the first area, this is a test screen
    StateChanger::set_state(STATE_TEST);
    StateChanger::change_state();

    // main game loop, states have logic and render functions
    // that direct the flow of the game
    while (window.isOpen()) {
        StateChanger::get_state()->logic(window);
        StateChanger::change_state();
        StateChanger::get_state()->render(window);
    }
    return 0;
}
