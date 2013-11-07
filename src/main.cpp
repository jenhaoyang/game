#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "State.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    window.setMouseCursorVisible(false);
    StateChanger::set_state(STATE_TEST);
    StateChanger::change_state();
    while (window.isOpen()) {
        StateChanger::get_state()->logic(window);
        StateChanger::change_state();
        StateChanger::get_state()->render(window);
    }
    return 0;
}
