#include "EntityManager.h"
#include "State.h"

EntityManager::EntityManager() : clock() {}

EntityManager::~EntityManager() {
    std::for_each(entities.begin(), entities.end(), EntityDeallocator());
}

void EntityManager::add(std::string name, Entity* entity) {
    entities.insert(std::pair<std::string, Entity*>(name, entity));
}

void EntityManager::remove(std::string name) {
    EntityManager_iter results = entities.find(name);
    if (results != entities.end()) {
        delete results->second;
        entities.erase(results);
    }
}

Entity* EntityManager::get(std::string name) const {
    EntityManager_const_iter results = entities.find(name);
    if (results == entities.end())
        return NULL;
    return results->second;
}

int EntityManager::size() const {
    return entities.size();
}

void EntityManager::render() {
    for (EntityManager_const_iter iter = entities.begin(); iter != entities.end(); iter++) {
        StateChanger::window.draw(*(iter->second));
    }
}

void EntityManager::update() {
    float timeDelta = clock.getElapsedTime().asSeconds();
    clock.restart();
    for (EntityManager_const_iter iter = entities.begin(); iter != entities.end(); iter++)
        iter->second->update(timeDelta);
}
