#include <PhysicsEngine.h>
#include <math.h>

using namespace std;

PhysicalObject::PhysicalObject()
{
    F = new List<Force>();
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
    F->PushFront(newForce);
    return newForce;
}

void PhysicalObject::removeForce(Force *oldForce)
{
    ListIterator<Force> *i = new ListIterator<Force>(F);
    i->SetFirst();
    while (oldForce != i->GetCurrent())
    {
        i->Next();
    }
    i->Remove();
}

Force PhysicalObject::resultingForce()
{
    Force resF;
    if(!F->IsEmpty()){
        ListIterator<Force> *i = new ListIterator<Force>(F);
        i->SetFirst();
        do{
            resF.Df += (*i->GetCurrent()).Df * (*i->GetCurrent()).f;
            resF.f +=  (*i->GetCurrent()).f *  (*i->GetCurrent()).f;
            i->Next();
        }while(!i->IsLast());
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
    float dt = 0;//zeit, noch unberechnet, Platzhalter
    calc_acceleration();
    V.Dv = (V.Dv * V.v +A.Da * A.a *dt);
    V.Dv.unify();
    V.v = sqrt(V.v*V.v +A.a*A.a*dt*dt);
}
