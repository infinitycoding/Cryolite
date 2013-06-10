#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED


#include <vector.h>


class Camera
{
    public:
        Camera();
        Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_looking, GLfloat y_looking, GLfloat z_looking);
        ~Camera();


        pvector3D position;
        dvector3D looking_direction;
};


#endif
