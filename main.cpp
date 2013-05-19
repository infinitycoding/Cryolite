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
#include "include/controls.h"
#include "include/material.h"


#define GROUND_SIZE 50

//todo: textur klasse, scene klasse
bool printFPS = false;


void menue(void);

SDL_Surface* screen = NULL;
GLuint cube, floor;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image

// draw the ground of the scene

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

int main(int argc, char *argv[]){

    SDL mainwindow = SDL(640,480,SDL_OPENGL,"Cryolite Engine");     // Create the graphics window


    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 30 );
    //gluPerspective(90, 640/480, 0, 1.5 );

    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_BLEND);


    glTranslatef(0,0,-8.5);     // Move the camera to the starting position
    glEnable( GL_TEXTURE_2D );

    glEnable(GL_MULTISAMPLE);



    Material ground = Material("ground.bmp");   // Loads the ground texture
    Material IC = Material("textur.bmp");
    cube = IC.textureGL;
    floor = ground.textureGL;

    INIT_Controls(&mainwindow);

    // 2D Texute settings



    int lasttick = SDL_GetTicks();
    int currenttick = 0;

    while(1){ //render

        if(printFPS)
        {
            currenttick = SDL_GetTicks();
            printf("%.1f FPS\n",(1000/(float)(currenttick-lasttick)));
            lasttick = currenttick;
        }



        mainwindow.pollEvents();    // Eventhandler
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        draw_another_cube();
        glPushMatrix();
        glTranslatef(1,2,3);
        draw_another_cube();
        glPopMatrix();
        draw_cube();            // Draw a few objects
        draw_ground();

        rotation_handler();     // Rotates the camera if mouse moved
        move_handler();         // Moves the camera if key pressed

        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffera


    }

}
