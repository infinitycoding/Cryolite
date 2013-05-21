#include <GL/gl.h>
#include <GL/glu.h>
#include "include/models.h"

extern GLuint cube, floor;


void draw_ground()
{
glEnable(GL_TEXTURE_2D);
glBindTexture( GL_TEXTURE_2D, floor );

    glBegin( GL_QUADS );

        glTexCoord2i( 1, 0 );
          glVertex3f( -GROUND_SIZE, -3, GROUND_SIZE);
        glTexCoord2i( 0, 0 );
          glVertex3f(-GROUND_SIZE, -3, -GROUND_SIZE);
        glTexCoord2i( 0, 1 );
          glVertex3f(GROUND_SIZE, -3, -GROUND_SIZE);
        glTexCoord2i( 1, 1 );
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


void drawHUD(void)
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(10.0, 10.0);
    glVertex2f(0.0, 10.0);
glEnd();
}
