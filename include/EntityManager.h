#pragma once
#include "Entity.h"

typedef std::map<std::string, Entity*>::iterator EntityManager_iter;
typedef std::map<std::string, Entity*>::const_iterator EntityManager_const_iter;

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        void add(std::string name, Entity* entity);
        void remove(std::string name);
        int size() const;
        Entity* get(std::string name) const;

        void render();
        void update();

    private:
        std::map<std::string, Entity*> entities;
        sf::Clock clock;

        struct EntityDeallocator {
            void operator()(const std::pair<std::string, Entity*> & p) const {
                delete p.second;
            }
        };
};
