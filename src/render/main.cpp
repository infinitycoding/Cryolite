#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL_thread.h>
#include <SDL_image.h>



#include "object.h"
#include "sdl.h"
#include "controls.h"
#include "material.h"
#include "models.h"
#include "general_def.h"
#include "scene.h"
#ifdef _WIN32
#undef main
#endif

#define FOV 80

//todo: textur klasse, scene klasse
bool printFPS = false;
bool render = true;
float averageFPS = 0;


// draw the ground of the scene





int main(int argc, char *argv[]){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

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

    glLineWidth (LINEWIDTH);
    glTranslatef(STARTING_X, STARTING_Y, STARTING_Z);

    INIT_Controls(&mainwindow);

    Scene *mainScene = new Scene();
    INIT_Models(mainScene);
    GLUquadric *q =gluNewQuadric();


    // 2D Texute settings
    float lastFPS = 0;

    mainScene->lasttick = SDL_GetTicks(); //better calculation

    while(render){ //render
        for(int i = 0; i<9;i++)
        {
            printf("\b");
        }

        if(printFPS && (lastFPS<=mainScene->averageFPS-0.05 || lastFPS>=mainScene->averageFPS+0.05))
        {

            printf ("%4.1f FPS",mainScene->averageFPS);
            lastFPS = mainScene->averageFPS;
        }


        mainwindow.pollEvents();    // Eventhandler

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);

        rotation_handler();     // Rotates the camera if mouse moved
        move_handler();         // Moves the camera if key pressed

        mainScene->render();
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        gluSphere(q,5,20,20);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


        drawHUD();

        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffera


    }

}
