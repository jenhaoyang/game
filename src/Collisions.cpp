#include "Collisions.h"
#include "Entity.h"

void MyContactListener::BeginContact(b2Contact* contact) {
    Entity* EntityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* EntityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    void* fixtureDataA = (Entity*)contact->GetFixtureA()->GetUserData();
    void* fixtureDataB = (Entity*)contact->GetFixtureB()->GetUserData();

    EntityA->BeginContact(EntityB, fixtureDataA);
    EntityB->BeginContact(EntityA, fixtureDataB);
}

void MyContactListener::EndContact(b2Contact* contact) {
    Entity* EntityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* EntityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    void* fixtureDataA = (Entity*)contact->GetFixtureA()->GetUserData();
    void* fixtureDataB = (Entity*)contact->GetFixtureB()->GetUserData();

    EntityA->EndContact(EntityB, fixtureDataA);
    EntityB->EndContact(EntityA, fixtureDataB);
}
