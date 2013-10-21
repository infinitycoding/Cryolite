#include <SDL.h>
#include <math.h>

#include <camera.h>
#include <general_def.h>



Camera::Camera()
{
    relativeToObject = NULL;
    localPosition = vector();

    lookingDirection = vector(0, 0, 1);

    nearClip = STANDART_NEARCLIP;
    farClip = STANDART_FARCLIP;
    fov = STANDART_FOV;

    x = 0;
    y = 0;

    height = STANDART_HEIGHT;
    width = STANDART_WIDTH;
    activ = false;
}


Camera::Camera(Object *relObj, vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth)
{
    relativeToObject = relObj;
    localPosition = vector(&pos);

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
    lookingDirection.x = lookingDirection.x * cos(rotate) - lookingDirection.y * sin(rotate);
    lookingDirection.y = lookingDirection.x * sin(rotate) + lookingDirection.y * cos(rotate);
}

vector Camera::getPosition()
{
    if(relativeToObject == NULL)
        return localPosition;
    else
        return relativeToObject->getPosition() + localPosition;
}
