#include <physics/boundobjects.h>

/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

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

    // TODO

    boxAfter.base += pos;

    boxAfter.base.mul(scale);
    boxAfter.height.mul(scale);
    boxAfter.width.mul(scale);
    boxAfter.length.mul(scale);

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

    // TODO

    sphereAfter.center += pos;

    sphereAfter.center.mul(scale);
    sphereAfter.radian *= scale.largest();


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

    // TODO

    planeAfter.base += pos;

    planeAfter.base.mul(scale);
    planeAfter.widht.mul(scale);
    planeAfter.length.mul(scale);

    return planeAfter;
}


