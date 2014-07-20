#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
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


#include <util/List.h>
#include <object.h>



struct collision
{
    Object *obj1;
    Object *obj2;
    vector *collisionSpot;
};


class CollisionList
{
    public:
        CollisionList();
        CollisionList(List<Object> *objects);
        ~CollisionList();

        int checkCollisions();
        List<collision> *getCollisions();
        List<Object> *setObjectList(List<Object> *newObjList);

    protected:
        void clearCollisionList();
        bool approximate(Object *obj1, Object *obj2);
        bool collide(Object *obj1, Object *obj2);
        bool addCollision(Object *obj1, Object *obj2, vector *spot);

        bool vectorInBox(vector v, BoundBox box);
        bool vectorInSphere(vector v, BoundSphere sphere);

        vector *boxBoxCollision(BoundBox box1, BoundBox box2);
        vector *boxPlaneCollision(BoundBox box, BoundPlane plane);
        vector *boxSphereCollision(BoundBox box, BoundSphere sphere);
        vector *planePlaneCollision(BoundPlane plane1, BoundPlane plane2);
        vector *planeSphereCollision(BoundPlane plane, BoundSphere sphere);
        vector *sphereSphereCollision(BoundSphere sphere1, BoundSphere sphere2);

        List<Object> *objList;
        List<collision> *collList;
};



#endif // COLLISION_H_INCLUDED
