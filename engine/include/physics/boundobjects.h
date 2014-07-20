#ifndef BOUNDOBJECTS_H_INCLUDED
#define BOUNDOBJECTS_H_INCLUDED
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


#include <util/vector.h>
#include <util/general_structs.h>



class BoundBox         // Bound Box
{
    public:
        BoundBox();
        BoundBox(BoundBox *original);
        BoundBox(vector b, vector h, vector w, vector l);
        ~BoundBox();

        BoundBox preprocess(vector pos, vector scale, struct rotation rot);

        vector base;
        vector height;
        vector width;
        vector length;
};


class BoundSphere      // Bound Sphere
{
    public:
        BoundSphere();
        BoundSphere(BoundSphere *original);
        BoundSphere(vector c, GLfloat r);
        ~BoundSphere();

        BoundSphere preprocess(vector pos, vector scale, rotation rot);

        vector center;
        GLfloat radian;
};


class BoundPlane       // Bound Plane
{
    public:
        BoundPlane();
        BoundPlane(BoundPlane *original);
        BoundPlane(vector b, vector w, vector l);
        ~BoundPlane();

        BoundPlane preprocess(vector pos, vector scale, rotation rot);

        vector base;
        vector widht;
        vector length;
};



#endif
