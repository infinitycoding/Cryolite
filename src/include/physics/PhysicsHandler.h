#ifndef PHYSICSHANDLER_H
#define PHYSICSHANDLER_H

#include <physics/PhysicsProperty.h>

class PhysicsHandler
{
    public:
        PhysicsHandler();
        virtual ~PhysicsHandler();

        void registerEntity(PhysicsProperty p);
        void disposeEntity(int id);

        List<PhysicsProperty> registeredEntities;


    protected:
    private:
};

#endif // PHYSICSHANDLER_H
