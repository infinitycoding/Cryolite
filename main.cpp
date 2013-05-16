#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL_thread.h>
#include <SDL_image.h>

#include "include/object.h"
#include "include/sdl.h"
#include "include/modelview.h"

void menue(void);

SDL_Surface* screen = NULL;
GLuint IC, Ground;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image

void draw_ground()
{
glBindTexture( GL_TEXTURE_2D, Ground );

    glBegin( GL_QUADS );

        glTexCoord2i( 1, 0 );
          glVertex3f( -30, -3, 30);
        glTexCoord2i( 0, 0 );
          glVertex3f(-30, -3, -30);
        glTexCoord2i( 0, 1 );
          glVertex3f(30, -3, -30);
        glTexCoord2i( 1, 1 );
          glVertex3f( 30, -3, 30);

    glEnd();
}

void draw_cube()
{
glBindTexture( GL_TEXTURE_2D, Ground);


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



int main(int argc, char *argv[]){

    //menue();

    screen = init_SDL(640,480,SDL_OPENGL,"Cryolite Engine");


    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 24 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_BLEND);


    glTranslatef(0,0,-3.5);
    glEnable( GL_TEXTURE_2D );

    glEnable(GL_MULTISAMPLE);



    //IC = loadTexture2D("textur.bmp");
    Ground = loadTexture2D("ground.bmp");

    // 2D Texute settings
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


    while(1){ //render
        process_events();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glFrustum( x1_left, x1_right, x2_left, x2_right, x3_left, x3_right );

        //renderObject(entity, &position);
        draw_cube();
        draw_ground();

        rotation_handler();
        move_handler();

        SDL_GL_SwapBuffers();

    }

}

