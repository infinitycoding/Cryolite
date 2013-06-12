#include <camera.h>



Camera::Camera()
{
    position = vector();

    looking_direction = vector(0, 0, 1);
}


Camera::Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_looking, GLfloat y_looking, GLfloat z_looking)
{
    position = vector(x_pos, y_pos, z_pos);

    looking_direction = vector(x_looking, y_looking, z_looking);
    looking_direction.unify();
}

Camera::~Camera()
{

}
