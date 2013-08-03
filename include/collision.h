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
};



#endif
