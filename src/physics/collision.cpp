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
            spot = boxBoxCollision(preprocessBoundBox(boxIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundBox(boxIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = boxPlaneCollision(preprocessBoundBox(boxIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundPlane(planeIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = boxSphereCollision(preprocessBoundBox(boxIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundSphere(sphereIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

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
            spot = boxPlaneCollision(preprocessBoundBox(boxIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot), preprocessBoundPlane(planeIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planePlaneCollision(preprocessBoundPlane(planeIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundPlane(planeIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = planeSphereCollision(preprocessBoundPlane(planeIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundSphere(sphereIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

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
            spot = boxSphereCollision(preprocessBoundBox(boxIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot), preprocessBoundSphere(sphereIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            boxIterator2.Next();
        }

        boxIterator2.SetFirst();

        while(!planeIterator2.IsLast())
        {
            spot = planeSphereCollision(preprocessBoundPlane(planeIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot), preprocessBoundSphere(sphereIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot));

            if(addCollision(obj1, obj2, spot))
                return true;

            planeIterator2.Next();
        }

        planeIterator2.SetFirst();

        while(!sphereIterator2.IsLast())
        {
            spot = sphereSphereCollision(preprocessBoundSphere(sphereIterator1.GetCurrent(), obj1->getPosition(), obj1->scale, obj1->rot), preprocessBoundSphere(sphereIterator2.GetCurrent(), obj2->getPosition(), obj2->scale, obj2->rot));

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


vector *CollisionList::boxBoxCollision(boundBox box1, boundBox box2)
{
    // TODO

    return NULL;
}


vector *CollisionList::boxPlaneCollision(boundBox box, boundPlane plane)
{
    // TODO

    return NULL;
}


vector *CollisionList::boxSphereCollision(boundBox box, boundSphere sphere)
{
    // TODO

    return NULL;
}


vector *CollisionList::planePlaneCollision(boundPlane plane1, boundPlane plane2)
{
    // TODO

    return NULL;
}


vector *CollisionList::planeSphereCollision(boundPlane plane, boundSphere sphere)
{
    // TODO

    return NULL;
}


vector *CollisionList::sphereSphereCollision(boundSphere sphere1, boundSphere sphere2)
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


boundBox CollisionList::cloneBoundBox(boundBox *boxtemplate)
{
    boundBox clone;

    clone.base = vector(&boxtemplate->base);
    clone.height = vector(&boxtemplate->height);
    clone.length = vector(&boxtemplate->length);
    clone.width = vector(&boxtemplate->width);

    return clone;
}


boundPlane CollisionList::cloneBoundPlane(boundPlane *planetemplate)
{
    boundPlane clone;

    clone.base = vector(&planetemplate->base);
    clone.widht = vector(&planetemplate->widht);
    clone.length = vector(&planetemplate->length);

    return clone;
}


boundSphere CollisionList::cloneBoundSphere(boundSphere *spheretemplate)
{
    boundSphere clone;

    clone.center = vector(&spheretemplate->center);
    clone.radian = spheretemplate->radian;

    return clone;
}


boundBox CollisionList::preprocessBoundBox(boundBox *boxBefore, vector pos, vector scale, rotation rot)
{
    boundBox boxAfter;

    boxAfter = cloneBoundBox(boxBefore);

    return boxAfter;
}


boundPlane CollisionList::preprocessBoundPlane(boundPlane *planeBefore, vector pos, vector scale, rotation rot)
{
    boundPlane planeAfter;

    planeAfter = cloneBoundPlane(planeBefore);

    return planeAfter;
}


boundSphere CollisionList::preprocessBoundSphere(boundSphere *sphereBefore, vector pos, vector scale, rotation rot)
{
    boundSphere sphereAfter;

    sphereAfter = cloneBoundSphere(sphereBefore);

    sphereAfter.center += pos;

    return sphereAfter;
}

