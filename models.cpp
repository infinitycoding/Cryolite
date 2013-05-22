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

void draw_cube()
{
    glEnable(GL_TEXTURE_2D);
glBindTexture( GL_TEXTURE_2D, cube);


    glBegin( GL_QUADS );

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 0 );
          glVertex3f(-1, 1, 1);
          glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, 1);
          glTexCoord2i( 1, 1 );
          glVertex3f( 1, -1, 1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, -1, -1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, -1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f( 1, -1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f( 1, -1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, -1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, -1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, -1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f(-1, -1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f(-1, -1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, 1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, 1, -1);
          glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, 1);

  glEnd();

}


// draw a cube with colors instead of textures

void draw_another_cube()
{

   glBegin( GL_QUADS );

        glColor3f(256, 0, 0);
          glVertex3f( 1, 1, 5);
        glColor3f(256, 0, 0);
          glVertex3f(-1, 1, 5);
        glColor3f(256, 0, 0);
          glVertex3f(-1, -1, 5);
        glColor3f(256, 0, 0);
          glVertex3f( 1, -1, 5);

        glColor3f(0, 256, 256);
          glVertex3f( 1, 1, 3);
        glColor3f(0, 256, 256);
          glVertex3f( 1, -1, 3);
        glColor3f(0, 256, 256);
          glVertex3f(-1, -1, 3);
        glColor3f(0, 256, 256);
          glVertex3f(-1, 1, 3);

        glColor3f(0, 256, 0);
          glVertex3f( 1, 1, 3);
        glColor3f(0, 256, 0);
          glVertex3f( 1, 1, 5);
        glColor3f(0, 256, 0);
          glVertex3f( 1, -1, 5);
        glColor3f(0, 256, 0);
          glVertex3f( 1, -1, 3);

        glColor3f(0, 0, 256);
          glVertex3f( 1, -1, 3);
        glColor3f(0, 0, 256);
          glVertex3f( 1, -1, 5);
        glColor3f(0, 0, 256);
          glVertex3f(-1, -1, 5);
        glColor3f(0, 0, 256);
          glVertex3f(-1, -1, 3);

        glColor3f(256, 256, 0);
          glVertex3f(-1, -1, 3);
        glColor3f(256, 256, 0);
          glVertex3f(-1, -1, 5);
        glColor3f(256, 256, 0);
          glVertex3f(-1, 1, 5);
        glColor3f(256, 256, 0);
          glVertex3f(-1, 1, 3);

        glColor3f(256, 256, 256);
          glVertex3f( 1, 1, 5);
        glColor3f(256, 256, 256);
          glVertex3f( 1, 1, 3);
        glColor3f(256, 256, 256);
          glVertex3f(-1, 1, 3);
        glColor3f(256, 256, 256);
          glVertex3f(-1, 1, 5);

  glEnd();

}




void createObjectTriangle(Material *mat, Scene *sce)
{
    struct vertex3D *vertex = (struct vertex3D *)malloc(3*sizeof(struct vertex3D));
    struct vertex2D *texvertex = (struct vertex2D *)malloc(3*sizeof(struct vertex3D));
    struct triangle *first_triangle = (struct triangle *)malloc(sizeof(struct triangle));

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

    Object *triangle = new Object("triangle");

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


#define HOR 8
#define VERT 16
#define SCOPE 1


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
    glEnd();

}
