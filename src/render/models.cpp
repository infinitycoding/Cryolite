#include <models.h>
#include <material.h>
#include <font.h>
#include <settings.h>

Texture *MAN;
Object *iccube;


void INIT_Models(Scene *sce)
{
    iccube = new Object(OBJECT(iccube.obj), "iccube", vector(0, 0, 0));
    sce->addObject(iccube);

    Object *ground = new Object(OBJECT(ground.obj), "ground", vector(0, -3, 0));
    sce->addObject(ground);

    Object *woodcube = new Object(OBJECT(bettercube.obj), "Cube", vector(5, 0, 0));
    sce->addObject(woodcube);

    Object *gravelcube = new Object(OBJECT(cube.obj), "cube.001", vector(-5, 0, 0));
    sce->addObject(gravelcube);

    MAN = Material::TexCache->requestTexture(IMAGE(man.png));
}



extern Settings *gameSettings;

void drawHUD(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gameSettings->width, gameSettings->height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 0);

    glBegin(GL_QUADS);
            glVertex2f((gameSettings->width/2)-1, (gameSettings->height/2)-((gameSettings->width/100)*SCOPE));
            glVertex2f((gameSettings->width/2)+1, (gameSettings->height/2)-((gameSettings->width/100)*SCOPE));
            glVertex2f((gameSettings->width/2)+1, (gameSettings->height/2)+((gameSettings->width/100)*SCOPE));
            glVertex2f((gameSettings->width/2)-1, (gameSettings->height/2)+((gameSettings->width/100)*SCOPE));

            glVertex2f((gameSettings->width/2)-((gameSettings->width/100)*SCOPE), (gameSettings->height/2)-1);
            glVertex2f((gameSettings->width/2)-((gameSettings->width/100)*SCOPE), (gameSettings->height/2)+1);
            glVertex2f((gameSettings->width/2)+((gameSettings->width/100)*SCOPE), (gameSettings->height/2)+1);
            glVertex2f((gameSettings->width/2)+((gameSettings->width/100)*SCOPE), (gameSettings->height/2)-1);


    glEnd();

glBindTexture( GL_TEXTURE_2D, MAN->nr);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);


    glBegin(GL_QUADS);

            glColor4f(0, 0, 0.5f,0.5f);
            glTexCoord2i( 1,  0);
            glVertex2f(gameSettings->width-((gameSettings->width/100)*HOR), gameSettings->height-((gameSettings->height/100)*VERT));
            glTexCoord2i( 1,  1);
            glVertex2f(gameSettings->width-((gameSettings->width/100)*HOR), gameSettings->height-10);
            glTexCoord2i( 0,  1);
            glVertex2f(gameSettings->width-10, gameSettings->height-10);
            glTexCoord2i( 0,  0);
            glVertex2f(gameSettings->width-10, gameSettings->height-((gameSettings->height/100)*VERT));
            glColor4f(1, 1, 1,1);


    glEnd();
    glBindTexture( GL_TEXTURE_2D, 0);





    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
