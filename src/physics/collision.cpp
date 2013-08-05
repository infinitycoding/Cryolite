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
    collision *foundCollision = new collision();
    foundCollision->object1 = obj1;
    foundCollision->object2 = obj2;

    boundBox *actualBox1 = NULL;
    boundBox *actualBox2 = NULL;

    ListIterator<boundBox> B1 = *ListIterator<boundBox>(obj1->objType->boundBoxes).SetFirst();
    ListIterator<boundBox> B2 = *ListIterator<boundBox>(obj2->objType->boundBoxes).SetFirst();

    while(!B1.IsLast())
    {
        actualBox1 = B1.GetCurrent();

        B1.Next();

        B2.SetFirst();

        while(!B2.IsLast())
        {
            actualBox2 = B2.GetCurrent();

            B2.Next();

            if(boxBoxCollisionQAD(actualBox1, obj1->getPosition(), actualBox2, obj2->getPosition(), &foundCollision->position))
                return foundCollision;
        }
    }

    delete foundCollision;
    return NULL;
}


bool CollisionLocate::boxBoxCollisionQAD(boundBox *box1, vector bpos1, boundBox *box2, vector bpos2, vector *rpos)
{
    vector vertices1[8];
    vector vertices2[8];

    boxVertices(box1, vertices1);
    boxVertices(box2, vertices2);

    for(int i = 0; i < 8; i++)
        if(vectorInCube(vertices1[i] + bpos1, box2->base + bpos2, box2->base + vector(box2->width, box2->height, box2->length) + bpos2))
        {
            *rpos = vertices1[i] + bpos1;
            cout << "collision!" << endl;
            return true;
        }

    for(int i = 0; i < 8; i++)
        if(vectorInCube(vertices2[i] + bpos2, box1->base + bpos1, box1->base + vector(box1->width, box1->height, box1->length) + bpos1))
        {
            *rpos = vertices2[i] + bpos2;
            cout << "collision!" << endl;
            return true;
        }

    return false;
}


vector *CollisionLocate::boxVertices(boundBox *box, vector *result)
{
    result[0] = box->base;
    result[1] = box->base + vector(box->width, 0, 0);
    result[2] = box->base + vector(0, box->height, 0);
    result[3] = box->base + vector(0, 0, box->length);
    result[4] = box->base + vector(box->width, box->height, 0);
    result[5] = box->base + vector(box->width, 0, box->length);
    result[6] = box->base + vector(0, box->height, box->length);
    result[7] = box->base + vector(box->width, box->height, box->length);

    return result;

}


bool CollisionLocate::vectorInCube(vector v, vector cstart, vector cend)
{
    return ((v.x >= cstart.x && v.x <= cend.x) && (v.y >= cstart.y && v.y <= cend.y) && (v.z >= cstart.z && v.z <= cend.z));
}
