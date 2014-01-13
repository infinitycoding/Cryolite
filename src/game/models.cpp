#include <models.h>
#include <material.h>
#include <font.h>

Texture *MAN;
Object *iccube;
Object *gravelcube;


void INIT_Models(Scene *sce)
{
    Font stdFonts = Font();
    stdFonts.loadTTF(FONT(arial.ttf), "stdarial", 10);

    iccube = new Object(OBJECT(iccube.obj), "iccube", vector(0, 0, 0));
    boundSphere *bs = new boundSphere;
    bs->center = vector(0, 0, 0);
    bs->radian = 1.0;
    iccube->objType->boundSpheres->PushFront(bs);
    sce->addObject(iccube);

    Object *ground = new Object(OBJECT(ground.obj), "ground", vector(0, -3, 0));
    sce->addObject(ground);

    Object *woodcube = new Object(OBJECT(bettercube.obj), "Cube", vector(5, 0, 0));
    bs = new boundSphere;
    bs->center = vector(0, 0, 0);
    bs->radian = 1.0;
    woodcube->objType->boundSpheres->PushFront(bs);
    sce->addObject(woodcube);

    gravelcube = new Object(OBJECT(cube.obj), "cube.001", vector(-5, 0, 0));
    //gravelcube->objType->ObjectTypeMaterial->ambiantTexture->nr = stdFonts.atotex("Test!\n", "stdarial");
    sce->addObject(gravelcube);

    MAN = Material::TexCache->requestTexture(IMAGE(man.png));
    //MAN->nr = stdFonts.atotex("Test!", "stdarial");
}



void drawHUD(float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 0);

    glBegin(GL_QUADS);
            glVertex2f((width/2)-1, (height/2)-((width/100)*SCOPE));
            glVertex2f((width/2)+1, (height/2)-((width/100)*SCOPE));
            glVertex2f((width/2)+1, (height/2)+((width/100)*SCOPE));
            glVertex2f((width/2)-1, (height/2)+((width/100)*SCOPE));

            glVertex2f((width/2)-((width/100)*SCOPE), (height/2)-1);
            glVertex2f((width/2)-((width/100)*SCOPE), (height/2)+1);
            glVertex2f((width/2)+((width/100)*SCOPE), (height/2)+1);
            glVertex2f((width/2)+((width/100)*SCOPE), (height/2)-1);


    glEnd();

glBindTexture( GL_TEXTURE_2D, MAN->nr);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);


    glBegin(GL_QUADS);

            glColor4f(0, 0, 0.5f,0.5f);
            glTexCoord2i( 1,  0);
            glVertex2f(width-((width/100)*HOR), height-((height/100)*VERT));
            glTexCoord2i( 1,  1);
            glVertex2f(width-((width/100)*HOR), height-10);
            glTexCoord2i( 0,  1);
            glVertex2f(width-10, height-10);
            glTexCoord2i( 0,  0);
            glVertex2f(width-10, height-((height/100)*VERT));
            glColor4f(1, 1, 1,1);


    glEnd();
    glBindTexture( GL_TEXTURE_2D, 0);





    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
