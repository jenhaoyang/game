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
