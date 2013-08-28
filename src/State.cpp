#include "State.h"

void MainScreen::logic(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void MainScreen::render(sf::RenderWindow& window) {
    window.clear();
    window.display();
}

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
                break;
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
