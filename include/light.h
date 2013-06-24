#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED


#include <GL/gl.h>
#include <GL/glu.h>



class Light
{
    public:
        Light();
        ~Light();


    private:
        GLfloat ambiantLightning[4];
        GLfloat diffuseLightning[4];
        GLfloat position[3];
        GLfloat spotDirection[3];
};

class Lamp
{
    public:

};


#endif
