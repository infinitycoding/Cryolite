#include <SDL.h>
#include <math.h>

#include <camera.h>
#include <general_def.h>



Camera::Camera()
{
    position = vector();
    lookingDirection = vector(0.0, 0.0, 1.0);

    nearClip = STANDART_NEARCLIP;
    farClip = STANDART_FARCLIP;
    fov = FOV;

    x = 0;
    y = 0;

    height = HEIGHT;
    width = WIDTH;
    activ = false;
}


Camera::Camera(vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth)
{
    position = vector(&pos);
    lookingDirection = vector(&looking);
    lookingDirection.unify();

    nearClip = nClip;
    farClip = fClip;
    fov = viewfield;

    x = vpx;
    y = vpy;

    height = vpheight;
    width = vpwidth;
    activ = true;
}

Camera::~Camera()
{

}

void Camera::rotateX(float rotate)
{
    lookingDirection.elements[1] = lookingDirection.elements[1] * cos(rotate) + lookingDirection.elements[2] * sin(rotate);
    lookingDirection.elements[2] = lookingDirection.elements[2] * cos(rotate) - lookingDirection.elements[1] * sin(rotate);
}

void Camera::rotateY(float rotate)
{
    lookingDirection.elements[0] = lookingDirection.elements[0] * cos(rotate) - lookingDirection.elements[2] * sin(rotate);
    lookingDirection.elements[2] = lookingDirection.elements[0] * sin(rotate) + lookingDirection.elements[2] * cos(rotate);
}

void Camera::rotateZ(float rotate)
{
    lookingDirection.elements[0] = lookingDirection.elements[1] * cos(rotate) + lookingDirection.elements[0] * sin(rotate);
    lookingDirection.elements[1] = lookingDirection.elements[0] * cos(rotate) - lookingDirection.elements[1] * sin(rotate);
}
