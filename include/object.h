#ifndef OBJECT_H
#define OBJECT_H


#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "material.h"
#include "list.h"



struct triangle
{
    uint32_t vertex[3];
};

struct square
{
    uint32_t vertex[4];
};

class Object
{
    public:
        Object();
        Object(const char *);
        ~Object();
        void addVertices(struct vertex3D *);
        void addTriangle(struct triangle *);
        void addSquare(struct square *);
        void loadMaterial(const char *);
        void loadObjectFile(const char *);

        uint32_t numofSpots;
        uint32_t numofTriangles;
        uint32_t numofSquares;
        struct List *vertices;
        struct List *triangles;
        struct List *squares;
        Material ObjectMaterial;
};






#endif
