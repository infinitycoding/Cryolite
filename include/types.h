#ifndef TYPES_H
#define TYPES_H

#define color_t unsigned char

struct colorRGBA
{
    color_t red;
    color_t green;
    color_t blue;
    color_t transparency;
};

struct colorRGB
{
    color_t red;
    color_t green;
    color_t blue;
};

struct vertex2D{
    GLfloat x;
    GLfloat y;
};

struct vertex3D{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

#endif

