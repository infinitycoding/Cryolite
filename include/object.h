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
        Object(const char *objname);
        Object(const char *filename, const char *objname);
        ~Object();

        struct vertex3D *addObjectVertex(struct vertex3D *new_vertex);
        struct vertex2D *addTextureVertex(struct vertex2D *new_tex_vertex);
        void addTriangle(struct triangle *new_triangle);
        void addSquare(struct square *new_square);
        void loadMaterial(const char *file);
        void loadObjectFile(const char *objectFile, const char *objectName);

        char objectname[20];

        uint32_t numofTextureSpots;
        uint32_t numofSpots;
        uint32_t numofTriangles;
        uint32_t numofSquares;

        struct vertex3D scale;
        struct vertex3D position;
        struct vertex3D rotationAxis;
        struct colorRGBA colorKey;
        GLfloat rotationAngle;

        struct vertex3D movement;
        float velocity;
        uint32_t remaining_movement;

        struct List *vertices;
        struct List *texvertices;
        struct List *triangles;
        struct List *squares;
        Material *ObjectMaterial;


    private:
        void initObject();
};






#endif
