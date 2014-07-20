#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
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


#include <object.h>



class Camera
{
    public:

        Camera();
        Camera(Object *relObj, vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth);

        ~Camera();


        void rotateX(float rotate);
        void rotateY(float rotate);
        void rotateZ(float rotate);

        void setViewportPos(int newX, int newY);
        void setViewportDim(int newHeight, int newWidth);

        vector getPosition();


        Object *relativeToObject;
        vector localPosition;

        vector lookingDirection;

        GLfloat nearClip;
        GLfloat farClip;
        GLfloat fov;

        GLint x;
        GLint y;

        GLint height;
        GLint width;

        bool activ;
};


#endif
