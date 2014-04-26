#include <physics/collision.h>



CollisionList::CollisionList()
{
    objList = NULL;
    collList = new List<collision>();
}


CollisionList::CollisionList(List<Object> *objects)
{
    objList = objects;
    collList = new List<collision>();
}


CollisionList::~CollisionList()
{

}


int CollisionList::checkCollisions()
{
    int counter = 0;

    ListIterator<Object> objIterator1 = *ListIterator<Object>(objList).SetFirst();
    ListIterator<Object> objIterator2 = *ListIterator<Object>(objList).SetFirst();

    clearCollisionList();

    while(!objIterator1.IsLast())
    {
        while(!objIterator2.IsLast())
        {
            if(objIterator1.GetCurrent() == objIterator2.GetCurrent())
            {
                objIterator2.Next();
                continue;
            }

            if(approximate(objIterator1.GetCurrent(), objIterator2.GetCurrent()))
                if(collide(objIterator1.GetCurrent(), objIterator2.GetCurrent()))
                    counter++;

            objIterator2.Next();
        }

        objIterator1.Next();
        objIterator2.SetFirst();
    }

    return counter;
}


List<collision> *CollisionList::getCollisions()
{
    return collList;
}


List<Object> *CollisionList::setObjectList(List<Object> *newObjList)
{
    return (objList = newObjList);
}


void CollisionList::clearCollisionList()
{
    ListIterator<collision> cleaner = *ListIterator<collision>(collList).SetFirst();

    while(!cleaner.IsEmpty())
    {
        delete cleaner.GetCurrent()->collisionSpot;
        cleaner.Remove();
    }
}


bool CollisionList::approximate(Object *obj1, Object *obj2)
{
    vector distance = obj1->getPosition() - obj2->getPosition();
    return (fabs(distance.len()) < (obj1->approximationSphere + obj2->approximationSphere));
}


bool CollisionList::collide(Object *obj1, Object *obj2)
{
    vector *spot = NULL;

    ListIterator<BoundBox> boxIterator1 = *ListIterator<BoundBox>(obj1->objType->boundBoxes).SetFirst();
    ListIterator<BoundBox> boxIterator2 = *ListIterator<BoundBox>(obj2->objType->boundBoxes).SetFirst();
    ListIterator<BoundPlane> planeIterator1 = *ListIterator<BoundPlane>(obj1->objType->boundPlanes).SetFirst();
    ListIterator<BoundPlane> planeIterator2 = *ListIterator<BoundPlane>(obj2->objType->boundPlanes).SetFirst();
    ListIterator<BoundSphere> sphereIterator1 = *ListIterator<BoundSphere>(obj1->objType->boundSpheres).SetFirst();
    ListIterator<BoundSphere> sphereIterator2 = *ListIterator<BoundSphere>(obj2->objType->boundSpheres).SetFirst();

    while(!boxIterator1.IsLast())
    {
        while(!boxIterator2.IsLast())
        {
            spot = boxBoxCollision(boxIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), boxIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = boxPlaneCollision(boxIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), planeIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = boxSphereCollision(boxIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), sphereIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            sphereIterator2.Next();
        }

        sphereIterator2.SetFirst();

        boxIterator1.Next();
    }

    boxIterator2.SetFirst();
    planeIterator2.SetFirst();
    sphereIterator2.SetFirst();

    while(!planeIterator1.IsLast())
    {
        while(!boxIterator2.IsLast())
        {
            spot = boxPlaneCollision(boxIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot), planeIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planePlaneCollision(planeIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), planeIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = planeSphereCollision(planeIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), sphereIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            sphereIterator2.Next();
        }

        sphereIterator2.SetFirst();

        planeIterator1.Next();
    }

    boxIterator2.SetFirst();
    planeIterator2.SetFirst();
    sphereIterator2.SetFirst();

    while(!sphereIterator1.IsLast())
    {
        while(!boxIterator2.IsLast())
        {
            spot = boxSphereCollision(boxIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot), sphereIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planeSphereCollision(planeIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot), sphereIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = sphereSphereCollision(sphereIterator1.GetCurrent()->preprocess(obj1->getPosition(), obj1->scale, obj1->rot), sphereIterator2.GetCurrent()->preprocess(obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            sphereIterator2.Next();
        }

        sphereIterator2.SetFirst();

        sphereIterator1.Next();
    }

    return false;
}


bool CollisionList::addCollision(Object *obj1, Object *obj2, vector *spot)
{
    collision *newCollision = NULL;

    if(spot != NULL)
    {
        ListIterator<collision> i(collList);
        i.SetFirst();

        while(!i.IsLast())
        {
            if(i.GetCurrent()->obj1 == obj2 && i.GetCurrent()->obj2 == obj1)
                return false;

            i.Next();
        }


        newCollision = new collision;

        newCollision->obj1 = obj1;
        newCollision->obj2 = obj2;
        newCollision->collisionSpot = spot;

        collList->PushFront(newCollision);

        return true;
    }

    return false;
}


bool CollisionList::vectorInBox(vector v, BoundBox box)
{
    if(v.x[0] > box.base.x[0] && v.x[1] > box.base.x[1] && v.x[2] > box.base.x[2] && v.x[0] < (box.base.x[0] + box.width.x[0]) && v.x[1] < (box.base.x[1] + box.height.x[1]) && v.x[2] < (box.base.x[2] + box.length.x[2]))
        return true;

    return false;
}


bool CollisionList::vectorInSphere(vector v, BoundSphere sphere)
{
    float distance = fabs((v - sphere.center).len());

    if(distance < sphere.radian)
        return true;

    return false;
}


vector *CollisionList::boxBoxCollision(BoundBox box1, BoundBox box2)
{
    vector vertex1[8];
    vector vertex2[8];

    vertex1[0] = box1.base;
    vertex1[1] = box1.base + box1.height;
    vertex1[2] = box1.base + box1.length;
    vertex1[3] = box1.base + box1.width;
    vertex1[4] = box1.base + box1.height + box1.length;
    vertex1[5] = box1.base + box1.height + box1.width;
    vertex1[6] = box1.base + box1.length + box1.width;
    vertex1[7] = box1.base + box1.height + box1.length + box1.width;

    vertex2[0] = box2.base;
    vertex2[1] = box2.base + box2.height;
    vertex2[2] = box2.base + box2.length;
    vertex2[3] = box2.base + box2.width;
    vertex2[4] = box2.base + box2.height + box2.length;
    vertex2[5] = box2.base + box2.height + box2.width;
    vertex2[6] = box2.base + box2.length + box2.width;
    vertex2[7] = box2.base + box2.height + box2.length + box2.width;

    for(int i = 0; i < 8; i++)
        if(vectorInBox(vertex1[i], box2) == true)
            return new vector(vertex1[i]);

    for(int i = 0; i < 8; i++)
        if(vectorInBox(vertex2[i], box1) == true)
            return new vector(vertex2[i]);

    return NULL;
}


vector *CollisionList::boxPlaneCollision(BoundBox box, BoundPlane plane)
{
    // TODO

    return NULL;
}


vector *CollisionList::boxSphereCollision(BoundBox box, BoundSphere sphere)
{
    vector vertex[8];

    vertex[0] = box.base;
    vertex[1] = box.base + box.height;
    vertex[2] = box.base + box.length;
    vertex[3] = box.base + box.width;
    vertex[4] = box.base + box.height + box.length;
    vertex[5] = box.base + box.height + box.width;
    vertex[6] = box.base + box.length + box.width;
    vertex[7] = box.base + box.height + box.length + box.width;

    for(int i = 0; i < 8; i++)
        if(vectorInSphere(vertex[i], sphere) == true)
            return new vector(vertex[i]);

    return NULL;
}


vector *CollisionList::planePlaneCollision(BoundPlane plane1, BoundPlane plane2)
{
    // TODO

    return NULL;
}


vector *CollisionList::planeSphereCollision(BoundPlane plane, BoundSphere sphere)
{
    // TODO

    return NULL;
}


vector *CollisionList::sphereSphereCollision(BoundSphere sphere1, BoundSphere sphere2)
{
    vector distance;
    vector helper1;
    vector helper2;
    vector *spot = NULL;

    distance = sphere1.center - sphere2.center;

    if(fabs(distance.len()) < (sphere1.radian + sphere2.radian))
    {
        spot = new vector();
        helper1 = sphere1.center - sphere2.center;
        helper1.unify();
        helper1 *= sphere2.radian;
        helper1 += sphere2.center;
        helper2 = sphere2.center - sphere1.center;
        helper2.unify();
        helper2 *= sphere1.radian;
        helper2 += sphere1.center;
        spot->setvalue((helper1 + helper2) * 0.5);
        return spot;
    }

    return NULL;
}

