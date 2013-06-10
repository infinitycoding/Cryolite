#include <camera.h>



Camera::Camera()
{
    position = {0, 0, 0};

    looking_direction = {0, 0, 1};
}


Camera::Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_looking, GLfloat y_looking, GLfloat z_looking)
{
    position = {x_pos, y_pos, z_pos};

    looking_direction = {x_looking, y_looking, z_looking};
    looking_direction = vunify(looking_direction);
}

Camera::~Camera()
{

}
