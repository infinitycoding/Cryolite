#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED



#include <object.h>



class Camera
{
    public:

        Camera();
        Camera(Object *relObj, vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth);

        ~Camera();


        void rotateX(float rotate);
        void rotateY(float rotate);
        void rotateZ(float rotate);

        void setViewportPos(int newX, int newY);
        void setViewportDim(int newHeight, int newWidth);

        vector getPosition();


        Object *relativeToObject;
        vector localPosition;

        vector lookingDirection;

        GLfloat nearClip;
        GLfloat farClip;
        GLfloat fov;

        GLint x;
        GLint y;

        GLint height;
        GLint width;

        bool activ;
};


#endif
