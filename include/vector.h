#ifndef VECTOR_H
#define VECTOR_H
#include <GL/gl.h>

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
}vector3D;

typedef struct{
    GLfloat x;
    GLfloat y;
}vector2D;


#define NULLVECTOR3D {0,0,0}
#define NULLVECTOR2D {0,0}

typedef vector3D dvector3D;
typedef vector3D pvector3D;


typedef vector2D dvector2D;
typedef vector2D pvector2D;


float vlen(vector3D v);
float vlen(vector2D v);

float vlen(vector3D *v);
float vlen(vector2D *v);


vector3D vunify(vector3D v);
vector2D vunify(vector2D v);

vector3D *vunify(vector3D *v);
vector2D *vunify(vector2D *v);

vector3D vunifyc(vector3D *v);
vector2D vunifyc(vector2D *v);


vector3D vadd(vector3D a,vector3D b);
vector2D vadd(vector2D a,vector2D b);

vector3D *vadd(vector3D *a,vector3D *b);
vector2D *vadd(vector2D *a,vector2D *b);

vector3D vaddc(vector3D *dest,vector3D *b);
vector2D vaddc(vector2D *dest,vector2D *b);

// SUB = a-b
vector3D vsub(vector3D a,vector3D b);
vector2D vsub(vector2D a,vector2D b);

vector3D *vsub(vector3D *a,vector3D *b);
vector2D *vsub(vector2D *a,vector2D *b);

vector3D vsubc(vector3D *dest,vector3D *b);
vector2D vsubc(vector2D *dest,vector2D *b);


vector3D vscale(float s,vector3D v);
vector2D vscale(float s,vector2D v);

vector3D *vscale(float s,vector3D *v);
vector2D *vscale(float s,vector2D *v);

vector3D vscalec(float s,vector3D *v);
vector2D vscalec(float s,vector2D *v);




#endif
