#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "State.h"

StateChanger statechanger;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    window.setMouseCursorVisible(false);
    statechanger.set_state(STATE_TEST);
    statechanger.change_state();
    while (window.isOpen()) {
        statechanger.get_state()->logic(window);
        statechanger.change_state();
        statechanger.get_state()->render(window);
    }
    return 0;
}
