#ifndef BOUNDOBJECTS_H_INCLUDED
#define BOUNDOBJECTS_H_INCLUDED



struct boundBox         // Bound Box
{
    vector base;
    vector height;
    vector width;
    vector length;
};

struct boundSphere      // Bound Sphere
{
    vector center;
    GLfloat radian;
};

struct boundPlane       // Bound Plane
{
    vector base;
    vector widht;
    vector length;
};


// from here on unused, don't know why i did this
enum boundObjectType
{
    uninitialized = 0,
    unknown = 0,
    unsupported = 0,
    box,
    sphere,
    plane
};


union boundObjectUnion
{
    boundBox b;
    boundSphere s;
    boundPlane p;
};


struct boundObject
{
    boundObjectType type;
    boundObjectUnion data;
};


#endif
