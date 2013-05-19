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


void menue(void);

SDL_Surface* screen = NULL;
GLuint cube, floor;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image

void draw_ground()
{
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

void draw_cube()
{
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

void endprogramm(SDL_Event *event)
{
    exit(0);
}

int main(int argc, char *argv[]){

    //menue();

    SDL mainwindow = SDL(640,480,SDL_OPENGL,"Cryolite Engine");


    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 30 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_BLEND);


    glTranslatef(0,0,-8.5);
    glEnable( GL_TEXTURE_2D );

    glEnable(GL_MULTISAMPLE);




    mainwindow.addEvent(SDL_QUIT,endprogramm);
    Material ground = Material("ground.bmp");
    //Material IC = Material("textur.bmp");
    //cube = IC.textureGL;
    floor = ground.textureGL;

    INIT_Controls(&mainwindow);

    // 2D Texute settings
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );




    while(1){ //render
        mainwindow.pollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //renderObject(entity, &position);
        draw_cube();
        draw_another_cube();
        draw_ground();

        rotation_handler();
        move_handler();

        SDL_GL_SwapBuffers();

    }

}

