#include "Collisions.h"
#include "Entity.h"

void MyContactListener::BeginContact(b2Contact* contact) {
    Entity* EntityA = (Entity*)contact->GetFixtureA()->GetUserData();
    Entity* EntityB = (Entity*)contact->GetFixtureB()->GetUserData();
}

void MyContactListener::EndContact(b2Contact* contact) {

}
