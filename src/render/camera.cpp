#include <SDL.h>

#include <camera.h>
#include <general_def.h>



Camera::Camera()
{
    position = vector();
    lookingDirection = vector(0.0, 0.0, 1.0);

    moveDirection = vector();
    motionDestination = vector();

    nearClip = STANDART_NEARCLIP;
    farClip = STANDART_FARCLIP;
    fov = FOV;

    x = 0;
    y = 0;

    height = HEIGHT;
    width = WIDTH;

    acceleration = 0;
    velocity = 0;

    timeMotionStart = 0;
    remeaningDistance = 0;
}


Camera::Camera(vector pos, vector looking, GLfloat nClip, GLfloat fClip, GLfloat viewfield, GLint vpx, GLint vpy, GLint vpheight, GLint vpwidth)
{
    position = vector(&pos);
    lookingDirection = vector(&looking);
    lookingDirection.unify();

    moveDirection = vector();
    motionDestination = vector();

    nearClip = nClip;
    farClip = fClip;
    fov = viewfield;

    x = vpx;
    y = vpy;

    height = vpheight;
    width = vpwidth;

    acceleration = 0;
    velocity = 0;

    timeMotionStart = 0;
    remeaningDistance = 0;
}

Camera::~Camera()
{

}

void Camera::moveCamera(float newVelocity, float newAcceleration, float length , vector direction)
{
    int currentTime = SDL_GetTicks();
    //normize Direction
    direction.unify();

    float completeVelocity = velocity+(acceleration*((currentTime-timeMotionStart)/1000));

    // calculate System V0
    velocity = len((direction*newVelocity)+(moveDirection*completeVelocity));

    // calculate new acceleration
    acceleration = len((direction*newAcceleration)+(moveDirection*acceleration));


    // calculate remeaning distance
    remeaningDistance = len((direction*length)+(moveDirection*remeaningDistance));


    // generate Direction Vector
    moveDirection = unify(moveDirection+direction);


    //calculate final position
    motionDestination = (moveDirection*remeaningDistance)+(position);

    // save current time
    timeMotionStart = currentTime;
}
