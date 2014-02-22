#include "Collision.h"
#include "State.h"

bool collides(const Entity& ent1, const std::string& ent_key) {
    return ent1.getGlobalBounds().intersects(StateChanger::get_state()->entity_manager.get(ent_key)->getGlobalBounds());
}
