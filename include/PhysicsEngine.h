#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include <vector.h>


struct Force{
    float f;
    vector Df;
};

struct Acceleration{
    float a;
    vector Da;
};

struct Velocity{
    float v;
    vector Dv;
};

class PhysicalObject
{
    public:

    PhysicalObject();
    PhysicalObject(List<Force> *initF, Acceleration initA, Velocity initV,float initm);
    ~PhysicalObject();

    Force* addForce(Force *newForce);
    void removeForce(Force *oldForce);
    Force resultingForce();
    void calc_acceleration();
    void calc_velocity();


    List<Force> *F;
    Acceleration A;
    Velocity V;
    float m;



};

#endif // PHYSICSENGINE_H
