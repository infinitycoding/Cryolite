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

        vector *boxBoxCollision(boundBox box1, boundBox box2);
        vector *boxPlaneCollision(boundBox box, boundPlane plane);
        vector *boxSphereCollision(boundBox box, boundSphere sphere);
        vector *planePlaneCollision(boundPlane plane1, boundPlane plane2);
        vector *planeSphereCollision(boundPlane plane, boundSphere sphere);
        vector *sphereSphereCollision(boundSphere sphere1, boundSphere sphere2);

        boundBox cloneBoundBox(boundBox *boxtemplate);
        boundPlane cloneBoundPlane(boundPlane *planetemplate);
        boundSphere cloneBoundSphere(boundSphere *spheretemplate);

        boundBox preprocessBoundBox(boundBox *boxBefore, vector pos, vector scale, rotation rot);
        boundPlane preprocessBoundPlane(boundPlane *planeBefore, vector pos, vector scale, rotation rot);
        boundSphere preprocessBoundSphere(boundSphere *sphereBefore, vector pos, vector scale, rotation rot);

        List<Object> *objList;
        List<collision> *collList;
};



#endif // COLLISION_H_INCLUDED
