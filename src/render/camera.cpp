#include <SDL.h>
#include <math.h>

#include <camera.h>
#include <general_def.h>
#include <settings.h>


extern Settings *gameSettings;


Camera::Camera()
{
    position = vector();
    lookingDirection = vector(0.0, 0.0, 1.0);

    nearClip = STANDART_NEARCLIP;
    farClip = STANDART_FARCLIP;
    fov = FOV;

    x = 0;
    y = 0;

    height = gameSettings->height;
    width = gameSettings->width;
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
    lookingDirection.y = lookingDirection.y * cos(rotate) + lookingDirection.z * sin(rotate);
    lookingDirection.z = lookingDirection.z * cos(rotate) - lookingDirection.y * sin(rotate);
}

void Camera::rotateY(float rotate)
{
    lookingDirection.x = lookingDirection.x * cos(rotate) - lookingDirection.z * sin(rotate);
    lookingDirection.z = lookingDirection.x * sin(rotate) + lookingDirection.z * cos(rotate);
}

void Camera::rotateZ(float rotate)
{
    lookingDirection.x = lookingDirection.y * cos(rotate) + lookingDirection.x * sin(rotate);
    lookingDirection.y = lookingDirection.x * cos(rotate) - lookingDirection.y * sin(rotate);
}
