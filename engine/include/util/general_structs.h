#ifndef GENERAL_STRUCTS_H_INCLUDED
#define GENERAL_STRUCTS_H_INCLUDED

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



enum success
{
    successful, failture
};


struct rotation
{
    GLfloat Angle;
    vector rotationAxis;
};



#endif // GENERAL_STRUCTS_H_INCLUDED
