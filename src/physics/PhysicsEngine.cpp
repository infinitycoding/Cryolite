#include <PhysicsEngine.h>
#include <math.h>

using namespace std;

PhysicalObject::PhysicalObject()
{
    F = new List<Force>;
    A.a = 0;
    V.v = 0;
    m = 1;
}

PhysicalObject::PhysicalObject(List<Force> *initF, Acceleration initA, Velocity initV,float initm)
{
    //F = initF;
    A.a = initA.a;
    A.Da = (initA.Da).unifyc();
    V.v = initV.v;
    V.Dv = (initV.Dv).unifyc();
    m = initm;
}

PhysicalObject::~PhysicalObject()
{
    delete F;
}






Force* PhysicalObject::addForce(Force *newForce)
{
    (*newForce).Df.unify();
    F ->ListPushFront(newForce);
    return newForce;
}

void PhysicalObject::removeForce(Force *oldForce)
{
    F ->ListSetFirst();
    while (oldForce != F->ListGetCurrent()){
        F->ListNext();
    };
    F ->ListRemove();
}

Force PhysicalObject::resultingForce()
{
    Force resF;
    if(!F->ListIsEmpty()){
        F->ListSetFirst();
        do{
            resF.Df += (*F->ListGetCurrent()).Df * (*F->ListGetCurrent()).f;
            resF.f +=  (*F->ListGetCurrent()).f *  (*F->ListGetCurrent()).f;
            F->ListNext();
        }while(!F->ListIsLast());
    };
    resF.f = sqrt(resF.f);
    resF.Df.unify();
    return resF;
}

void PhysicalObject::calc_acceleration()
{
    Force tempForce = resultingForce();
    A.Da = tempForce.Df;
    A.a = tempForce.f / m;
}

void PhysicalObject::calc_velocity()
{
    float dt;//zeit, noch unberechnet, Platzhalter
    calc_acceleration();
    V.Dv = (V.Dv * V.v +A.Da * A.a *dt);
    V.Dv.unify();
    V.v = sqrt(V.v*V.v +A.a*A.a*dt*dt);
}
