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


#include <SDL.h>
#include <math.h>

#include <camera.h>
#include <util/general_def.h>


Camera::Camera()
{
    relativeToObject = NULL;
    localPosition = vector();

    lookingDirection = vector(0, 0, 1);

    nearClip = STANDART_NEARCLIP;
    farClip = STANDART_FARCLIP;
    fov = STANDART_FOV;
}


Camera::Camera(Object *relObj, vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield)
{
    relativeToObject = relObj;
    localPosition = vector(&pos);

    lookingDirection = vector(&looking);
    lookingDirection.unify();

    nearClip = nClip;
    farClip = fClip;
    fov = viewfield;
}

Camera::~Camera()
{

}

void Camera::rotateX(float rotate)
{
    lookingDirection.x[1] = lookingDirection.x[1] * cos(rotate) + lookingDirection.x[2] * sin(rotate);
    lookingDirection.x[2] = lookingDirection.x[2] * cos(rotate) - lookingDirection.x[1] * sin(rotate);
    lookingDirection.unify();
}

void Camera::rotateY(float rotate)
{
    lookingDirection.x[0] = lookingDirection.x[0] * cos(rotate) - lookingDirection.x[2] * sin(rotate);
    lookingDirection.x[2] = lookingDirection.x[0] * sin(rotate) + lookingDirection.x[2] * cos(rotate);
    lookingDirection.unify();
}

void Camera::rotateZ(float rotate)
{
    lookingDirection.x[0] = lookingDirection.x[0] * cos(rotate) - lookingDirection.x[1] * sin(rotate);
    lookingDirection.x[1] = lookingDirection.x[0] * sin(rotate) + lookingDirection.x[1] * cos(rotate);
    lookingDirection.unify();
}


vector Camera::getPosition()
{
    if(relativeToObject == NULL)
        return localPosition;
    else
        return relativeToObject->getPosition() + localPosition;
}
