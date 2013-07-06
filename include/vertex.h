#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED



/*****************************************************
 * Vertex-Module                                     *
 * -------------                                     *
 *                                                   *
 * Contains the two vertex classes. Not many         *
 * functions in the moment.                          *
 *                                                   *
 * created by Peter Hösch                            *
 *****************************************************/



#include <GL/gl.h>

#include <iostream>



class Vertex2D
{
    public:
        Vertex2D();
        Vertex2D(GLfloat startX, GLfloat startY);
        ~Vertex2D();

        GLfloat getX() const;
        GLfloat getY() const;

        void set(GLfloat newX, GLfloat newY);
        void setX(GLfloat newX);
        void setY(GLfloat newY);

    protected:
        GLfloat x;
        GLfloat y;
};

std::ostream& operator << (std::ostream& stream, Vertex2D const v);



class Vertex3D
{
    public:
        Vertex3D();
        Vertex3D(GLfloat startX, GLfloat startY, GLfloat startZ);
        ~Vertex3D();

        GLfloat getX() const;
        GLfloat getY() const;
        GLfloat getZ() const;

        void set(GLfloat newX, GLfloat newY, GLfloat newZ);
        void setX(GLfloat newX);
        void setY(GLfloat newY);
        void setZ(GLfloat newZ);

    protected:
        GLfloat x;
        GLfloat y;
        GLfloat z;
};

std::ostream& operator << (std::ostream& stream, Vertex3D const  v);

#endif
