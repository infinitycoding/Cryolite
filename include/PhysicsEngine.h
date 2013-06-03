#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include <List.h>


class PhysicsEngine
{
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();
        List *addActor();
        void update();
        void initEngine();
    protected:
    private:
};

#endif // PHYSICSENGINE_H
