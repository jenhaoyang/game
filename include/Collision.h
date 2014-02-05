#pragma once
#include "Entity.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

bool near_ground(const Entity& ent1, const Entity& ent2, float distance);
