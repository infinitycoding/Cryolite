#ifndef OBJECT_H
#define OBJECT_H


#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "types.h"









class Object
{
    public:
        Object();
        ~Object();
        void addMaterial();
        void addVertices();

        uint32_t numofSpots;
        uint32_t numofTriangles;
        uint32_t numofSquares;
        struct List *vertices;
        struct List *triangles;
        struct List *Squares;
};






#endif
