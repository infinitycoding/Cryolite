#ifndef BOUNDOBJECTS_H_INCLUDED
#define BOUNDOBJECTS_H_INCLUDED



#include <vector.h>
#include <general_structs.h>



class BoundBox         // Bound Box
{
    public:
        BoundBox();
        BoundBox(BoundBox *original);
        BoundBox(vector b, vector h, vector w, vector l);
        ~BoundBox();

        BoundBox preprocess(vector pos, vector scale, struct rotation rot);

        vector base;
        vector height;
        vector width;
        vector length;
};

class BoundSphere      // Bound Sphere
{
    public:
        BoundSphere();
        BoundSphere(BoundSphere *original);
        BoundSphere(vector c, GLfloat r);
        ~BoundSphere();

        BoundSphere preprocess(vector pos, vector scale, rotation rot);

        vector center;
        GLfloat radian;
};

class BoundPlane       // Bound Plane
{
    public:
        BoundPlane();
        BoundPlane(BoundPlane *original);
        BoundPlane(vector b, vector w, vector l);
        ~BoundPlane();

        BoundPlane preprocess(vector pos, vector scale, rotation rot);

        vector base;
        vector widht;
        vector length;
};



#endif
