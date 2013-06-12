#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <GL/gl.h>


#include <vector.h>


class Camera
{
    public:

        Camera();
        Camera(vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth);

        ~Camera();

        void moveCamera(float newVelocity, float newAccaleration, float length , vector direction);


        vector position;
        vector lookingDirection;

        vector moveDirection;

        vector motionDestination;

        GLfloat nearClip;
        GLfloat farClip;
        GLfloat fov;

        GLint x;
        GLint y;

        GLint height;
        GLint width;

        float acceleration;
        float velocity;

        int timeMotionStart;
        int remeaningDistance;
};


#endif
