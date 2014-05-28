#include "State.h"
#include "Collisions.h"
#include "SFMLDebugDraw.h"

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
MainScreen::MainScreen() : State() {
    Player* player = new Player(sf::Vector2f(0.82, 1.82), b2Vec2(300, 700), 3, 3, world);
    Ground* ground = new Ground(sf::Vector2f(13, 2), 7, 13, world);
    Ground* ground2 = new Ground(sf::Vector2f(2, 2), 4, 10, world);
    entity_manager.add("Player", player);
    entity_manager.add("Ground", ground);
    entity_manager.add("Ground2", ground2);
    
    SFMLDebugDraw* debugDraw = new SFMLDebugDraw(StateChanger::window);
    debugDraw->SetFlags(b2Draw::e_shapeBit);
    world->SetDebugDraw(debugDraw);

    MyContactListener* myContactListener = new MyContactListener;
    world->SetContactListener(myContactListener);
}

// check events and do movement
// basically anything that isn't rendering
void MainScreen::logic() {
    sf::Event event;
    while (StateChanger::window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            StateChanger::set_state(STATE_CLOSE);
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            StateChanger::window.setView(sf::View(visibleArea));
        }
    }
    entity_manager.checkDestroy();
    entity_manager.update();
    world->Step(1.0f/60.0f, 10, 8);
}

// draw all objects to the screen
void MainScreen::render() {
    StateChanger::window.clear();
    entity_manager.render();
    //world->DrawDebugData();
    StateChanger::window.display();
}

// the initial state is NULL (different from STATE_NULL
State* StateChanger::current_state = NULL;
e_State StateChanger::next_state = STATE_NULL;
sf::RenderWindow StateChanger::window;
