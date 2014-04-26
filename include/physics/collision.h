#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED



#include <List.h>
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
