/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */


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


vector PhysicalObject::getImpulse()
{
    return impulse;
}


vector PhysicalObject::setImpulse(vector newImpulse)
{
    return (impulse = newImpulse);
}
