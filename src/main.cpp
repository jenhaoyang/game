#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "State.h"

StateChanger statechanger;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    window.setMouseCursorVisible(false);
    statechanger.changeState(STATE_TEST);
    while (window.isOpen()) {
        statechanger.current_state->logic(window);
        statechanger.update_state();
        statechanger.current_state->render(window);
    }
    return 0;
}
