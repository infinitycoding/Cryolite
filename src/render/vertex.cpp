#include <vertex.h>



Vertex2D::Vertex2D()
{
    x = 0.0;
    y = 0.0;
}


Vertex2D::Vertex2D(Vertex2D *v)
{
    x = v->x;
    y = v->y;
}


Vertex2D::Vertex2D(GLfloat startX, GLfloat startY)
{
    x = startX;
    y = startY;
}


Vertex2D::~Vertex2D()
{

}


GLfloat Vertex2D::getX() const
{
    return x;
}


GLfloat Vertex2D::getY() const
{
    return y;
}


void Vertex2D::set(GLfloat newX, GLfloat newY)
{
    x = newX;
    y = newY;
}


void Vertex2D::setX(GLfloat newX)
{
    x = newX;
}


void Vertex2D::setY(GLfloat newY)
{
    y = newY;
}


std::ostream& operator << (std::ostream& stream, Vertex2D const v)
{
    stream << "X:" << v.getX() << " Y:" << v.getY();
    return stream;
}





Vertex3D::Vertex3D()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}


Vertex3D::Vertex3D(Vertex3D *v)
{
    x = v->x;
    y = v->y;
    z = v->z;
}


Vertex3D::Vertex3D(GLfloat startX, GLfloat startY, GLfloat startZ)
{
    x = startX;
    y = startY;
    z = startZ;
}


Vertex3D::~Vertex3D()
{

}


GLfloat Vertex3D::getX() const
{
    return x;
}


GLfloat Vertex3D::getY() const
{
    return y;
}


GLfloat Vertex3D::getZ() const
{
    return z;
}

void Vertex3D::set(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}


void Vertex3D::setX(GLfloat newX)
{
    x = newX;
}


void Vertex3D::setY(GLfloat newY)
{
    y = newY;
}


void Vertex3D::setZ(GLfloat newZ)
{
    z = newZ;
}


std::ostream& operator << (std::ostream& stream, Vertex3D const v)
{
    stream << "X:" << v.getX() << " Y:" << v.getY() << " Z:" << v.getZ();
    return stream;
}
