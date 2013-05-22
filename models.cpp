#include "include/models.h"


extern GLuint cube, floor;


void draw_ground()
{
glEnable(GL_TEXTURE_2D);
glBindTexture( GL_TEXTURE_2D, floor );

    glBegin( GL_QUADS );

        glTexCoord2i( 50, 0 );
          glVertex3f( -GROUND_SIZE, -3, GROUND_SIZE);
        glTexCoord2i( 0, 0 );
          glVertex3f(-GROUND_SIZE, -3, -GROUND_SIZE);
        glTexCoord2i( 0, 50 );
          glVertex3f(GROUND_SIZE, -3, -GROUND_SIZE);
        glTexCoord2i( 50, 50 );
          glVertex3f( GROUND_SIZE, -3, GROUND_SIZE);

    glEnd();
}

// draw a cube with a texture

void createObjectCube(Material *mat, Scene *sce)
{
    struct vertex3D *vertex = (struct vertex3D *)malloc(8*sizeof(struct vertex3D));
    struct vertex2D *texvertex = (struct vertex2D *)malloc(4*sizeof(struct vertex2D));
    struct square *square = (struct square *)malloc(6*sizeof(struct square));

    Object *iccube = new Object("iccube");


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


void createObjectTriangle(Material *mat, Scene *sce)
{
    struct vertex3D *vertex = (struct vertex3D *)malloc(3*sizeof(struct vertex3D));
    struct vertex2D *texvertex = (struct vertex2D *)malloc(3*sizeof(struct vertex2D));
    struct triangle *first_triangle = (struct triangle *)malloc(sizeof(struct triangle));

    Object *triangle = new Object("triangle");

    vertex[0].x = 0.0;
    vertex[0].y = 0.0;
    vertex[0].z = 0.0;

    vertex[1].x = 5.0;
    vertex[1].y = 0.0;
    vertex[1].z = 0.0;

    vertex[2].x = 5.0;
    vertex[2].y = 5.0;
    vertex[2].z = 0.0;

    texvertex[0].x = 0.0;
    texvertex[0].y = 0.0;

    texvertex[1].x = 1.0;
    texvertex[1].y = 0.0;

    texvertex[2].x = 1.0;
    texvertex[2].y = 1.0;


    first_triangle->objVertex[0] = triangle->addObjectVertex(&vertex[0]);
    first_triangle->objVertex[1] = triangle->addObjectVertex(&vertex[1]);
    first_triangle->objVertex[2] = triangle->addObjectVertex(&vertex[2]);

    first_triangle->texVertex[0] = triangle->addTextureVertex(&texvertex[0]);
    first_triangle->texVertex[1] = triangle->addTextureVertex(&texvertex[1]);
    first_triangle->texVertex[2] = triangle->addTextureVertex(&texvertex[2]);

    triangle->addTriangle(first_triangle);
    triangle->ObjectMaterial = mat;
    sce->addObject(triangle);

    return;
}


void drawHUD(void)
{
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

            glColor4f(0, 0, 0.5f,0.5f);

            glVertex2f(WIDTH-((WIDTH/100)*HOR), HEIGHT-((HEIGHT/100)*VERT));
            glVertex2f(WIDTH-((WIDTH/100)*HOR), HEIGHT-10);
            glVertex2f(WIDTH-10, HEIGHT-10);
            glVertex2f(WIDTH-10, HEIGHT-((HEIGHT/100)*VERT));

            glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnd();

}
