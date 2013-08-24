#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED



#include <cmath>

#include <object.h>



struct collision
{
    Object *object1;
    Object *object2;
    vector position;
};


class CollisionLocate
{
    public:
        CollisionLocate();
        CollisionLocate(List<Object> *objList);
        ~CollisionLocate();

        void calculateCollisions();
        bool checkApproximation(Object *obj1, Object *obj2);
        collision *checkCollision(Object *obj1, Object *obj2);


        List<Object> *objects;
        List<collision> *collisions;

    protected:
        vector *boxVertices(boundBox *box, vector *result);
        bool vectorInCube(vector v, vector cstart, vector cend);

        bool boxBoxCollisionQAD(boundBox *box1, vector bpos1, boundBox *box2, vector bpos2, vector *rpos);
        bool sphereSphereCollision(boundSphere *sphere1, vector spos1, boundSphere *sphere2, vector spos2, vector *rpos);
};



#endif
