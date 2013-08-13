#include <PhysicsEngine.h>



using namespace std;



PhysicalObject::PhysicalObject()
{
    forces = new List<vector>;

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
    ListIterator<vector> F = *ListIterator<vector>(forces).SetFirst();
    vector *actualForce = NULL;

    if(forces->IsEmpty())
        return;

    while(!F.IsLast())
    {
        actualForce = F.GetCurrent();
        impulse += (*actualForce * (1.0 / fps));
        F.Next();
    }

    *position += (impulse * (1.0 / fps));
}