#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED


#include <GL/gl.h>
#include <GL/glu.h>

#include <object.h>
#include <List.h>

typedef enum
{
    lamp,
    object,
    none,
}relativt_t;


class LightManager
{
    public:
       LightManager();
       ~LightManager();

       GLint getLightNum();
       void returnLightNum(GLint n);

        List<GLint> *lightNums;
        int numCounter;
};


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

         void refreshPosition(void);
         void activate();
         void deactivate();

         void directed(bool b);
         bool isDirected(void);

         void setExponent(GLfloat e);
         void setCutOf(GLfloat c);

         void setConstAttenaution(GLfloat a);
         void setLinAttenaution(GLfloat a);
         void setQuadAttenaution(GLfloat a);

         void setStandart();

         void refresh();



        ~Lamp();

        vector getPosition();


        relativt_t getRelation();

        void setRelation(relativt_t r);
        void setRelation(Object *o);
        void setRelation(Lamp *l);

        vector localPosition;

        friend class Level;

        private:
        LightManager *LM;
        relativt_t rel;
        Object *relativeToObject;
        Lamp  *relativeToLamp;


        GLint Lightnum;
        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        GLfloat position[4];
        GLfloat direction[4];
        GLfloat exponent;
        GLfloat cutof;
        GLfloat ConstAttenaution;
        GLfloat LinAttenaution;
        GLfloat QuadAttenaution;
        bool activ;
        bool modified;
        bool reg;


};


#endif
