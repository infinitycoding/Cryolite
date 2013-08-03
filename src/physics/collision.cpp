#include <collision.h>



CollisionLocate::CollisionLocate()
{
    collisions = new List<collision>;
}


CollisionLocate::CollisionLocate(List<Object> *objList)
{
    collisions = new List<collision>;

    objects = objList;
}


CollisionLocate::~CollisionLocate()
{
    delete collisions;
}


void CollisionLocate::calculateCollisions(void)
{
    Object *obj1 = NULL;
    Object *obj2 = NULL;

    collision *newCollision = NULL;

    ListIterator<Object> I1 = *ListIterator<Object>(objects).SetFirst();
    ListIterator<Object> I2 = *ListIterator<Object>(objects).SetFirst();

    if(objects->IsEmpty())
        return;

    while(!I1.IsLast())
    {
        obj1 = I1.GetCurrent();

        I1.Next();

        I2.SetFirst();

        while(!I2.IsLast())
        {
            obj2 = I2.GetCurrent();

            I2.Next();

            if(obj1 == obj2)
                continue;

            if(checkApproximation(obj1, obj2))
            {
                newCollision = checkCollision(obj1, obj2);

                if(newCollision != NULL)
                    collisions->PushFront(newCollision);
            }
        }
    }
}


bool CollisionLocate::checkApproximation(Object *obj1, Object *obj2)
{
    float distance = fabs(len(obj1->getPosition() - obj2->getPosition()));
    float allowedDistance = obj1->approximationSphere + obj2->approximationSphere;
    return (distance < allowedDistance);
}


collision *CollisionLocate::checkCollision(Object *obj1, Object *obj2)
{
    return NULL;
}
