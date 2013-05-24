/*#include "PhysicsEngine.h"
#include "general_def.h"

PhysicsEngine::PhysicsEngine(Scene scene)
{
    initEngine();
}

PhysicsEngine::~PhysicsEngine()
{
    //dtor
}
void PhysicsEngine::initEngine(Scene scene)
{
actors = this.loadAllActors(scene) //actor list

numofObjects = ListSize(actors);

actorCache = new ActorCache(STANDARD_SIZED_CACHE); //cache of actors, which are currently simulated
}

List *PhysicsEngine::loadAllActors(Scene *scene)
{
actorsList = ListCreate()

ListSetFirst(scene->objectList);

while(!ListIsLast(scene->objectList))
    {
        if (ListGetCurrent(scene->objectList).isPhysicalActor)
            {
            ListPushBack(scene->objectList, ListGetCurrent(scene->objectList));
            }
    ListNext(scene->objectList);
    }


    return *actorsList;
}

void PhysicsEngine::addActor(Actor *newActor)
{
numofObjects++;

ListPushFront(actors, *newActor);
}

void PhysicsEngine::update(){




}*/
