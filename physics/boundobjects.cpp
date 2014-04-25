#include <physics/boundobjects.h>



BoundBox::BoundBox()
{
    base = vector();
    height = vector();
    width = vector();
    length = vector();
}


BoundBox::BoundBox(BoundBox *original)
{
    base = vector(&original->base);
    height = vector(&original->height);
    length = vector(&original->length);
    width = vector(&original->width);
}


BoundBox::BoundBox(vector b, vector h, vector w, vector l)
{
    base = b;
    height = h;
    width = w;
    length = l;
}


BoundBox::~BoundBox()
{

}


BoundBox BoundBox::preprocess(vector pos, vector scale, rotation rot)
{
    BoundBox boxAfter(this);

    boxAfter.base.mul(scale);
    boxAfter.height.mul(scale);
    boxAfter.width.mul(scale);
    boxAfter.length.mul(scale);

    // TODO

    boxAfter.base += pos;

    return boxAfter;
}


BoundSphere::BoundSphere()
{
    center = vector();
    radian = 0;
}


BoundSphere::BoundSphere(BoundSphere *original)
{
    center = vector(&original->center);
    radian = original->radian;
}


BoundSphere::BoundSphere(vector c, GLfloat r)
{
    center = c;
    radian = r;
}


BoundSphere::~BoundSphere()
{

}


BoundSphere BoundSphere::preprocess(vector pos, vector scale, rotation rot)
{
    BoundSphere sphereAfter(this);

    sphereAfter.center.mul(scale);
    sphereAfter.radian *= scale.largest();

    // TODO

    sphereAfter.center += pos;

    return sphereAfter;
}


BoundPlane::BoundPlane()
{
    base = vector();
    widht = vector();
    length = vector();
}


BoundPlane::BoundPlane(BoundPlane *original)
{
    base = vector(&original->base);
    widht = vector(&original->widht);
    length = vector(&original->length);
}


BoundPlane::BoundPlane(vector b, vector w, vector l)
{
    base = b;
    widht = w;
    length = l;
}


BoundPlane::~BoundPlane()
{

}


BoundPlane BoundPlane::preprocess(vector pos, vector scale, rotation rot)
{
    BoundPlane planeAfter(this);

    planeAfter.base.mul(scale);
    planeAfter.widht.mul(scale);
    planeAfter.length.mul(scale);

    // TODO

    planeAfter.base += pos;

    return planeAfter;
}


