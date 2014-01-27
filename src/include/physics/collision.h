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

        vector *boxBoxCollision(vector offset1, boundBox box1, vector offset2, boundBox box2);
        vector *boxPlaneCollision(vector offset1, boundBox box, vector offset2, boundPlane plane);
        vector *boxSphereCollision(vector offset1, boundBox box, vector offset2, boundSphere sphere);
        vector *planePlaneCollision(vector offset1, boundPlane plane1, vector offset2, boundPlane plane2);
        vector *planeSphereCollision(vector offset1, boundPlane plane, vector offset2, boundSphere sphere);
        vector *sphereSphereCollision(vector offset1, boundSphere sphere1, vector offset2, boundSphere sphere2);

        List<Object> *objList;
        List<collision> *collList;
};



#endif // COLLISION_H_INCLUDED
