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

    ListIterator<boundBox> boxIterator1 = *ListIterator<boundBox>(obj1->objType->boundBoxes).SetFirst();
    ListIterator<boundBox> boxIterator2 = *ListIterator<boundBox>(obj2->objType->boundBoxes).SetFirst();
    ListIterator<boundPlane> planeIterator1 = *ListIterator<boundPlane>(obj1->objType->boundPlanes).SetFirst();
    ListIterator<boundPlane> planeIterator2 = *ListIterator<boundPlane>(obj2->objType->boundPlanes).SetFirst();
    ListIterator<boundSphere> sphereIterator1 = *ListIterator<boundSphere>(obj1->objType->boundSpheres).SetFirst();
    ListIterator<boundSphere> sphereIterator2 = *ListIterator<boundSphere>(obj2->objType->boundSpheres).SetFirst();

    while(!boxIterator1.IsLast())
    {
        while(!boxIterator2.IsLast())
        {
            spot = boxBoxCollision(obj1->getPosition(), *boxIterator1.GetCurrent(), obj2->getPosition(), *boxIterator2.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = boxPlaneCollision(obj1->getPosition(), *boxIterator1.GetCurrent(), obj2->getPosition(), *planeIterator2.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = boxSphereCollision(obj1->getPosition(), *boxIterator1.GetCurrent(), obj2->getPosition(), *sphereIterator2.GetCurrent());

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
            spot = boxPlaneCollision(obj2->getPosition(), *boxIterator2.GetCurrent(), obj1->getPosition(), *planeIterator2.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planePlaneCollision(obj1->getPosition(), *planeIterator1.GetCurrent(), obj2->getPosition(), *planeIterator2.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = planeSphereCollision(obj1->getPosition(), *planeIterator1.GetCurrent(), obj2->getPosition(), *sphereIterator2.GetCurrent());

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
            spot = boxSphereCollision(obj2->getPosition(), *boxIterator2.GetCurrent(), obj1->getPosition(), *sphereIterator1.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planeSphereCollision(obj2->getPosition(), *planeIterator1.GetCurrent(), obj1->getPosition(), *sphereIterator2.GetCurrent());

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = sphereSphereCollision(obj1->getPosition(), *sphereIterator1.GetCurrent(), obj2->getPosition(), *sphereIterator2.GetCurrent());

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
            if(i.GetCurrent()->obj1 == obj2 && i.GetCurrent()->obj2 == obj1)
                return false;

        newCollision = new collision;

        newCollision->obj1 = obj1;
        newCollision->obj2 = obj2;
        newCollision->collisionSpot = spot;

        collList->PushFront(newCollision);

        return true;
    }

    return false;
}


vector *CollisionList::boxBoxCollision(vector offset1, boundBox box1, vector offset2, boundBox box2)
{
    // TODO

    return NULL;
}


vector *CollisionList::boxPlaneCollision(vector offset1, boundBox box, vector offset2, boundPlane plane)
{
    // TODO

    return NULL;
}


vector *CollisionList::boxSphereCollision(vector offset1, boundBox box, vector offset2, boundSphere sphere)
{
    // TODO

    return NULL;
}


vector *CollisionList::planePlaneCollision(vector offset1, boundPlane plane1, vector offset2, boundPlane plane2)
{
    // TODO

    return NULL;
}


vector *CollisionList::planeSphereCollision(vector offset1, boundPlane plane, vector offset2, boundSphere sphere)
{
    // TODO

    return NULL;
}


vector *CollisionList::sphereSphereCollision(vector offset1, boundSphere sphere1, vector offset2, boundSphere sphere2)
{
    vector distance;
    vector helper1;
    vector helper2;
    vector *spot = NULL;

    distance = (sphere1.center + offset1) - (sphere2.center + offset2);

    if(fabs(distance.len()) < (sphere1.radian + sphere2.radian))
    {
        spot = new vector();
        helper1 = (sphere1.center + offset1) - (sphere2.center + offset2);
        helper1.unify();
        helper1 *= sphere2.radian;
        helper1 += (sphere2.center + offset2);
        helper2 = (sphere2.center + offset2) - (sphere1.center + offset1);
        helper2.unify();
        helper2 *= sphere1.radian;
        helper2 += (sphere1.center + offset1);
        spot->setvalue((helper1 + helper2) * 0.5);
        return spot;
    }

    return NULL;
}
