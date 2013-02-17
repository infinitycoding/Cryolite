#ifndef OBJECT_H
#define OBJECT_H


#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#define vertex_t unsigned int
#define color_t unsigned char

struct color32{
    color_t red;
    color_t green;
    color_t blue;
    color_t transparency;
};

struct vertex{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct triangle{
    vertex_t p[3];
    color32  c[3];
};

struct ObjectFileHeader{
    uint32_t numofSpots;
    uint32_t numofTriangles;
};

struct object{
    uint32_t numofSpots;
    uint32_t numofTriangles;
    struct vertex   *vertices;
    struct triangle *triangles;
};

struct triangle_expl{
    struct triangle_expl *prev;
    struct triangle_expl *next;
    vertex_t    p[3];
    struct color32     c[3];
};

struct vertex_expl{
    struct vertex_expl *prev;
    struct vertex_expl *next;
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct object_expl{
    uint32_t               numofSpots;
    uint32_t               numofTriangles;
    struct vertex_expl     *vertices;
    struct triangle_expl   *triangles;
};


void renderObject(struct object *obj,vertex *position);
struct object *loadObject(const char *file);
int saveObject(struct object *obj,const char *file);
struct object_expl *createObject_expl(void);


#endif
