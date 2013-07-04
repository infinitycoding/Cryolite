#include <models.h>
#include <material.h>
#include <font.h>
#include <settings.h>

Material *MAN;
Object *iccube;


void INIT_Models(Scene *sce)
{
    Material *IC = new Material(IMAGE(textur.bmp));
    MAN = new Material(IMAGE(man.png));

    createObjectCube(IC, sce);

    Object *ground = new Object(OBJECT(ground.obj), "ground", vector(0, -3, 0));
    sce->addObject(ground);

    Object *woodcube = new Object(OBJECT(bettercube.obj), "Cube", vector(5, 0, 0));
    sce->addObject(woodcube);

    Object *gravelcube = new Object(OBJECT(cube.obj), "cube.001", vector(-5, 0, 0));
    sce->addObject(gravelcube);
}

// draw a cube with a texture

void createObjectCube(Material *mat, Scene *sce)
{
    vertex3D *vertex = new vertex3D[8];
    vertex2D *texvertex = new vertex2D[4];
    Polygone *square = new Polygone[6];

    iccube = new Object();


    texvertex[0].x = 1.0f;
    texvertex[0].y = 0.0f;

    texvertex[1].x = 0.0f;
    texvertex[1].y = 0.0f;

    texvertex[2].x = 0.0f;
    texvertex[2].y = 1.0f;

    texvertex[3].x = 1.0f;
    texvertex[3].y = 1.0f;


    vertex[0].x = 1;
    vertex[0].y = 1;
    vertex[0].z = 1;

    vertex[1].x = -1;
    vertex[1].y = 1;
    vertex[1].z = 1;

    vertex[2].x = -1;
    vertex[2].y = -1;
    vertex[2].z = 1;

    vertex[3].x = 1;
    vertex[3].y = -1;
    vertex[3].z = 1;

    vertex[4].x = 1;
    vertex[4].y = 1;
    vertex[4].z = -1;

    vertex[5].x = 1;
    vertex[5].y = -1;
    vertex[5].z = -1;

    vertex[6].x = -1;
    vertex[6].y = -1;
    vertex[6].z = -1;

    vertex[7].x = -1;
    vertex[7].y = 1;
    vertex[7].z = -1;


    square[0].setObjVertex(0, &vertex[0]);
    square[0].setObjVertex(1, &vertex[1]);
    square[0].setObjVertex(2, &vertex[2]);
    square[0].setObjVertex(3, &vertex[3]);
    square[0].setTexVertex(0, &texvertex[0]);
    square[0].setTexVertex(1, &texvertex[1]);
    square[0].setTexVertex(2, &texvertex[2]);
    square[0].setTexVertex(3, &texvertex[3]);

    square[1].setObjVertex(0, &vertex[4]);
    square[1].setObjVertex(1, &vertex[5]);
    square[1].setObjVertex(2, &vertex[6]);
    square[1].setObjVertex(3, &vertex[7]);
    square[1].setTexVertex(0, &texvertex[0]);
    square[1].setTexVertex(1, &texvertex[1]);
    square[1].setTexVertex(2, &texvertex[2]);
    square[1].setTexVertex(3, &texvertex[3]);

    square[2].setObjVertex(0, &vertex[4]);
    square[2].setObjVertex(1, &vertex[0]);
    square[2].setObjVertex(2, &vertex[3]);
    square[2].setObjVertex(3, &vertex[5]);
    square[2].setTexVertex(0, &texvertex[0]);
    square[2].setTexVertex(1, &texvertex[1]);
    square[2].setTexVertex(2, &texvertex[2]);
    square[2].setTexVertex(3, &texvertex[3]);

    square[3].setObjVertex(0, &vertex[5]);
    square[3].setObjVertex(1, &vertex[3]);
    square[3].setObjVertex(2, &vertex[2]);
    square[3].setObjVertex(3, &vertex[6]);
    square[3].setTexVertex(0, &texvertex[0]);
    square[3].setTexVertex(1, &texvertex[1]);
    square[3].setTexVertex(2, &texvertex[2]);
    square[3].setTexVertex(3, &texvertex[3]);

    square[4].setObjVertex(0, &vertex[6]);
    square[4].setObjVertex(1, &vertex[2]);
    square[4].setObjVertex(2, &vertex[1]);
    square[4].setObjVertex(3, &vertex[7]);
    square[4].setTexVertex(0, &texvertex[0]);
    square[4].setTexVertex(1, &texvertex[1]);
    square[4].setTexVertex(2, &texvertex[2]);
    square[4].setTexVertex(3, &texvertex[3]);

    square[5].setObjVertex(0, &vertex[0]);
    square[5].setObjVertex(1, &vertex[4]);
    square[5].setObjVertex(2, &vertex[7]);
    square[5].setObjVertex(3, &vertex[1]);
    square[5].setTexVertex(0, &texvertex[0]);
    square[5].setTexVertex(1, &texvertex[1]);
    square[5].setTexVertex(2, &texvertex[2]);
    square[5].setTexVertex(3, &texvertex[3]);



    iccube->addTextureVertex(&texvertex[0]);
    iccube->addTextureVertex(&texvertex[1]);
    iccube->addTextureVertex(&texvertex[2]);
    iccube->addTextureVertex(&texvertex[3]);


    iccube->addObjectVertex(&vertex[0]);
    iccube->addObjectVertex(&vertex[1]);
    iccube->addObjectVertex(&vertex[2]);
    iccube->addObjectVertex(&vertex[3]);
    iccube->addObjectVertex(&vertex[4]);
    iccube->addObjectVertex(&vertex[5]);
    iccube->addObjectVertex(&vertex[6]);
    iccube->addObjectVertex(&vertex[7]);


    iccube->addPolygone(&square[0]);
    iccube->addPolygone(&square[1]);
    iccube->addPolygone(&square[2]);
    iccube->addPolygone(&square[3]);
    iccube->addPolygone(&square[4]);
    iccube->addPolygone(&square[5]);


    iccube->ObjectMaterial = mat;


    sce->addObject(iccube);


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

glBindTexture( GL_TEXTURE_2D, MAN->textureGL);
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
