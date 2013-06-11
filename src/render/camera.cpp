#include <camera.h>



Camera::Camera()
{
    position.x = 0;
    position.y = 0;
    position.z = 0;

    looking_direction.x = 0;
    looking_direction.y = 0;
    looking_direction.z = 1;
}


Camera::Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_looking, GLfloat y_looking, GLfloat z_looking)
{
    position.x = x_pos;
    position.y = y_pos;
    position.z = z_pos;

    looking_direction.x = x_looking;
    looking_direction.y = y_looking;
    looking_direction.z = z_looking;

    looking_direction = vunify(looking_direction);
}

Camera::~Camera()
{

}
