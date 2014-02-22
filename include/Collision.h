#pragma once
#include "Entity.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

bool collides(const Entity& ent1, const std::string& ent_key);
