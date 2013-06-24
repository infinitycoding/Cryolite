#include <light.h>



Light::Light()
{
    ambiantLightning[0] = 0.2;
    ambiantLightning[1] = 0.2;
    ambiantLightning[2] = 0.2;
    ambiantLightning[3] = 1.0;

    diffuseLightning[0] = 1.0;
    diffuseLightning[1] = 1.0;
    diffuseLightning[2] = 0.3;
    diffuseLightning[3] = 0.5;

    position[0] = 5.0;
    position[1] = 0.0;
    position[2] = 0.0;

    spotDirection[0] = 0.0;
    spotDirection[1] = -1.0;
    spotDirection[2] = 0.0;

    //GLfloat emission[] = {0.8,0.0,1.0};
     GLfloat globalAmbient[4] = {0.0, 0.0, 0.0, 1.0};

    glEnable(GL_LIGHT0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambiantLightning);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightning);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
}


Light::~Light()
{
    glDisable(GL_LIGHT0);
}
