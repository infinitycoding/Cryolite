#include <light.h>



GlobalLight::GlobalLight()
{
    ambient[0] = 1.0;
    ambient[1] = 1.0;
    ambient[2] = 1.0;
    ambient[3] = 1.0;

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}


GlobalLight::GlobalLight(GLfloat ambientRed, GLfloat ambientGreen, GLfloat ambientBlue, GLfloat ambientTransparency )
{
    ambient[0] = ambientRed;
    ambient[1] = ambientGreen;
    ambient[2] = ambientBlue;
    ambient[3] = ambientTransparency;

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}

void GlobalLight::activateLight()
{
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}

GlobalLight::~GlobalLight()
{
    glDisable(GL_LIGHTING);
}
