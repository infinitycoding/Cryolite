#include <models.h>
#include <material.h>

Material *MAN;
Object *iccube;


void INIT_Models(Scene *sce)
{
    Material *ground = new Material(IMAGE(blacktile.jpg));   // Loads the ground texture
    Material *IC = new Material(IMAGE(textur.bmp));
    MAN = new Material(IMAGE(man.png));
    createObjectCube(IC, sce);
    createObjectGround(ground, sce);
    Object *woodcube = new Object(OBJECT(bettercube.obj), "Cube");
    woodcube->position.x = 5;
    sce->addObject(woodcube);
    Object *gravelcube = new Object(OBJECT(cube.obj), "cube.001");
    gravelcube->position.x = -5;
    sce->addObject(gravelcube);
}


void createObjectGround(Material *mat, Scene *sce)
{
    vertex3D *vertex = new vertex3D[4];
    vertex2D *texvertex = new vertex2D[4];
    struct square *square = new struct square;

    Object *ground = new Object("ground");

    vertex[0].x = -GROUND_SIZE;
    vertex[0].y = -3.0;
    vertex[0].z = GROUND_SIZE;

    vertex[1].x = -GROUND_SIZE;
    vertex[1].y = -3.0;
    vertex[1].z = -GROUND_SIZE;

    vertex[2].x = GROUND_SIZE;
    vertex[2].y = -3.0;
    vertex[2].z = -GROUND_SIZE;

    vertex[3].x = GROUND_SIZE;
    vertex[3].y = -3.0;
    vertex[3].z = GROUND_SIZE;


    texvertex[0].x = 0.0;
    texvertex[0].y = 0.0;

    texvertex[1].x = 50.0;
    texvertex[1].y = 0.0;

    texvertex[2].x = 50.0;
    texvertex[2].y = 50.0;

    texvertex[3].x = 0.0;
    texvertex[3].y = 50.0;


    square->objVertex[0] = ground->addObjectVertex(&vertex[0]);
    square->objVertex[1] = ground->addObjectVertex(&vertex[1]);
    square->objVertex[2] = ground->addObjectVertex(&vertex[2]);
    square->objVertex[3] = ground->addObjectVertex(&vertex[3]);

    square->texVertex[0] = ground->addTextureVertex(&texvertex[0]);
    square->texVertex[1] = ground->addTextureVertex(&texvertex[1]);
    square->texVertex[2] = ground->addTextureVertex(&texvertex[2]);
    square->texVertex[3] = ground->addTextureVertex(&texvertex[3]);

    ground->addSquare(square);

    ground->ObjectMaterial = mat;

    sce->addObject(ground);

    return;

}

// draw a cube with a texture

void createObjectCube(Material *mat, Scene *sce)
{
    vertex3D *vertex = new vertex3D[8];
    vertex2D *texvertex = new vertex2D[4];
    struct square *square = new struct square[6];

    iccube = new Object("iccube");


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


    square[0].objVertex[0] = &vertex[0];
    square[0].objVertex[1] = &vertex[1];
    square[0].objVertex[2] = &vertex[2];
    square[0].objVertex[3] = &vertex[3];
    square[0].texVertex[0] = &texvertex[0];
    square[0].texVertex[1] = &texvertex[1];
    square[0].texVertex[2] = &texvertex[2];
    square[0].texVertex[3] = &texvertex[3];

    square[1].objVertex[0] = &vertex[4];
    square[1].objVertex[1] = &vertex[5];
    square[1].objVertex[2] = &vertex[6];
    square[1].objVertex[3] = &vertex[7];
    square[1].texVertex[0] = &texvertex[0];
    square[1].texVertex[1] = &texvertex[1];
    square[1].texVertex[2] = &texvertex[2];
    square[1].texVertex[3] = &texvertex[3];

    square[2].objVertex[0] = &vertex[4];
    square[2].objVertex[1] = &vertex[0];
    square[2].objVertex[2] = &vertex[3];
    square[2].objVertex[3] = &vertex[5];
    square[2].texVertex[0] = &texvertex[0];
    square[2].texVertex[1] = &texvertex[1];
    square[2].texVertex[2] = &texvertex[2];
    square[2].texVertex[3] = &texvertex[3];

    square[3].objVertex[0] = &vertex[5];
    square[3].objVertex[1] = &vertex[3];
    square[3].objVertex[2] = &vertex[2];
    square[3].objVertex[3] = &vertex[6];
    square[3].texVertex[0] = &texvertex[0];
    square[3].texVertex[1] = &texvertex[1];
    square[3].texVertex[2] = &texvertex[2];
    square[3].texVertex[3] = &texvertex[3];

    square[4].objVertex[0] = &vertex[6];
    square[4].objVertex[1] = &vertex[2];
    square[4].objVertex[2] = &vertex[1];
    square[4].objVertex[3] = &vertex[7];
    square[4].texVertex[0] = &texvertex[0];
    square[4].texVertex[1] = &texvertex[1];
    square[4].texVertex[2] = &texvertex[2];
    square[4].texVertex[3] = &texvertex[3];

    square[5].objVertex[0] = &vertex[0];
    square[5].objVertex[1] = &vertex[4];
    square[5].objVertex[2] = &vertex[7];
    square[5].objVertex[3] = &vertex[1];
    square[5].texVertex[0] = &texvertex[0];
    square[5].texVertex[1] = &texvertex[1];
    square[5].texVertex[2] = &texvertex[2];
    square[5].texVertex[3] = &texvertex[3];



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


    iccube->addSquare(&square[0]);
    iccube->addSquare(&square[1]);
    iccube->addSquare(&square[2]);
    iccube->addSquare(&square[3]);
    iccube->addSquare(&square[4]);
    iccube->addSquare(&square[5]);


    iccube->ObjectMaterial = mat;



    sce->addObject(iccube);


}


void drawHUD(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 0);

    glBegin(GL_QUADS);
            glVertex2f((WIDTH/2)-1, (HEIGHT/2)-((WIDTH/100)*SCOPE));
            glVertex2f((WIDTH/2)+1, (HEIGHT/2)-((WIDTH/100)*SCOPE));
            glVertex2f((WIDTH/2)+1, (HEIGHT/2)+((WIDTH/100)*SCOPE));
            glVertex2f((WIDTH/2)-1, (HEIGHT/2)+((WIDTH/100)*SCOPE));

            glVertex2f((WIDTH/2)-((WIDTH/100)*SCOPE), (HEIGHT/2)-1);
            glVertex2f((WIDTH/2)-((WIDTH/100)*SCOPE), (HEIGHT/2)+1);
            glVertex2f((WIDTH/2)+((WIDTH/100)*SCOPE), (HEIGHT/2)+1);
            glVertex2f((WIDTH/2)+((WIDTH/100)*SCOPE), (HEIGHT/2)-1);


    glEnd();

glBindTexture( GL_TEXTURE_2D, MAN->textureGL);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);


    glBegin(GL_QUADS);

            glColor4f(0, 0, 0.5f,0.5f);
            glTexCoord2i( 1,  0);
            glVertex2f(WIDTH-((WIDTH/100)*HOR), HEIGHT-((HEIGHT/100)*VERT));
            glTexCoord2i( 1,  1);
            glVertex2f(WIDTH-((WIDTH/100)*HOR), HEIGHT-10);
            glTexCoord2i( 0,  1);
            glVertex2f(WIDTH-10, HEIGHT-10);
            glTexCoord2i( 0,  0);
            glVertex2f(WIDTH-10, HEIGHT-((HEIGHT/100)*VERT));
            glColor4f(1, 1, 1,1);


    glEnd();
    glBindTexture( GL_TEXTURE_2D, 0);





    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
