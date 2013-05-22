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
    struct vertex3D *objVertex[3];
    struct vertex2D *texVertex[3];
};

struct square
{
    struct vertex3D *objVertex[4];
    struct vertex2D *texVertex[4];
};

class Object
{
    public:
        Object();
        Object(const char *, const char *);
        ~Object();

        struct vertex3D *addObjectVertex(struct vertex3D *);
        struct vertex2D *addTextureVertex(struct vertex2D *);
        void addTriangle(struct triangle *);
        void addSquare(struct square *);
        void loadMaterial(const char *);
        void loadObjectFile(const char *, const char *);

        char objectname[20];

        uint32_t numofTextureSpots;
        uint32_t numofSpots;
        uint32_t numofTriangles;
        uint32_t numofSquares;

        struct vertex3D scale;
        struct vertex3D position;
        struct vertex3D rotationAxis;
        GLfloat rotationAngle;

        struct vertex3D movement;
        float velocity;
        uint32_t remaining_movement;

        struct List *vertices;
        struct List *texvertices;
        struct List *triangles;
        struct List *squares;
        Material ObjectMaterial;
};






#endif
