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
#include "include/models.h"
#include "include/general_def.h"
#include "include/scene.h"



#define FOV 80

//todo: textur klasse, scene klasse
bool printFPS = false;
int fpslenght = 0;
bool render = true;





SDL_Surface* screen = NULL;
GLuint cube, floor;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
Scene scene;

// draw the ground of the scene

void toggle_printFPS(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_f)
    {
        if(printFPS)
            printFPS = false;
        else
            printFPS = true;
    }

    return;
}



int main(int argc, char *argv[]){

    SDL mainwindow = SDL(WIDTH,HEIGHT,SDL_OPENGL|SDL_HWSURFACE,"Cryolite Engine");     // Create the graphics window


    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 100 );
    //gluPerspective(FOV, WIDTH/HEIGHT, 1.5, 100 );

    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glEnable( GL_TEXTURE_2D );

    glEnable(GL_MULTISAMPLE_ARB);







    Material ground = Material("blacktile.jpg");   // Loads the ground texture
    Material IC = Material("textur.bmp");
    cube = IC.textureGL;
    floor = ground.textureGL;

    INIT_Controls(&mainwindow);
    mainwindow.addEvent(SDL_KEYDOWN,toggle_printFPS);

    createObjectTriangle(&IC, &scene);

    // 2D Texute settings



    int lasttick = SDL_GetTicks();
    int currenttick = 0;

    while(render){ //render

        if(printFPS)
        {
            currenttick = SDL_GetTicks();
            for(int i =0;i<fpslenght;i++)
            {
                printf("\b");
            }
            char buffer[10] = {0,0,0,0,0,0,0,0,0,0};
            fpslenght = sprintf (buffer,"%.1f FPS",(1000/(float)(currenttick-lasttick)));
            printf("%s",buffer);
            lasttick = currenttick;
        }



        mainwindow.pollEvents();    // Eventhandler



        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);

        rotation_handler();     // Rotates the camera if mouse moved
        move_handler();         // Moves the camera if key pressed

        draw_another_cube();

        glPushMatrix();
        glTranslatef(1,2,3);
        draw_another_cube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5, 3, 0);
        glScalef(2, 2, 2);
        draw_cube();
        glPopMatrix();

        scene.render();

        draw_cube();            // Draw a few objects
        draw_ground();


        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glLoadIdentity();

        drawHUD();

        glPopMatrix();

        glMatrixMode(GL_PROJECTION);

        glPopMatrix();





        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffera


    }

}
