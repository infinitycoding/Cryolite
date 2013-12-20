#include <physics/PhysicsEngine.h>



using namespace std;



PhysicalObject::PhysicalObject()
{
    forces = new List<vector>();

    impulse = vector();

    mass = 1;
}


PhysicalObject::PhysicalObject(List<vector> *initForces, vector initImpulse, float initMass)
{
    forces = initForces;

    impulse = initImpulse;

    mass = initMass;
}


PhysicalObject::~PhysicalObject()
{
    delete forces;
}


void PhysicalObject::interpolatePhysics(vector *position, float fps)
{
    ListIterator<vector> F(forces);
    vector *currentForce = NULL;

    F.SetFirst();

    if(!forces->IsEmpty())
    {
        while(!F.IsLast())
        {
            currentForce = F.GetCurrent();
            impulse += (*currentForce * (1.0 / fps));
            F.Next();
        }
    }

    *position += (impulse * (1.0 / mass) * (1.0 / fps));
}


vector *PhysicalObject::addForce(vector *newForce)
{
    forces->PushFront(newForce);
    return newForce;
}
