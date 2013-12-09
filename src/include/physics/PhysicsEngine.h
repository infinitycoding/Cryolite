#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H



#include <math.h>

#include <vector.h>



class PhysicalObject
{
    public:
        PhysicalObject();
        PhysicalObject(List<vector> *initForces, vector initImpulse, float initMass);
        ~PhysicalObject();

        void interpolatePhysics(vector *position, float fps);

    private:
        List<vector> *forces;
        vector impulse;

        float mass;
};

#endif
