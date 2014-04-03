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

        vector *addForce(vector *newForce);

        vector getImpulse();
        vector setImpulse(vector newImpulse);

    protected:
        List<vector> *forces;
        vector impulse;

        float mass;
};

#endif
