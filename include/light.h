#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED


#include <GL/gl.h>
#include <GL/glu.h>

#include <object.h>


typedef enum
{
    constant,
    linear,
    quadric
}attenaution_t;



class GlobalLight
{
    public:
        GlobalLight();
        GlobalLight(GLfloat ambientRed, GLfloat ambientGreen, GLfloat ambientBlue, GLfloat ambientTransparency );
        void activateLight();
        ~GlobalLight();

        GLfloat ambient[4];
};


class Lamp
{
    public:
         Lamp();
         Lamp(Lamp *L);
         Lamp(Lamp *L, vector pos);
         Lamp(Lamp *L, vector pos, vector dir);

         Lamp(Lamp *L, vector *pos);
         Lamp(Lamp *L, vector *pos, vector *dir);


         void setAmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t);
         void setDiffuseLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t);
         void setSpecularLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t);

         void setAmbientLight(GLfloat *L);
         void setDiffuseLight(GLfloat *L);
         void setSpecularLight(GLfloat *L);

         void setDirection(vector d);
         void setDirection(vector *d);
         void setDirection(GLfloat *L);


         void setPosition(vector p);
         void setPosition(vector *p);
         void setPosition(GLfloat *L);

         void directed(bool b);
         bool isDirected(void);

         void setStandart();

        ~Lamp();

        GLint Lightnum;
        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        GLfloat position[4];
        GLfloat direction[4];
        GLfloat exponent;
        GLfloat cutof;
        attenaution_t attType;
        GLfloat attenaution;
        bool activ;

};


#endif
