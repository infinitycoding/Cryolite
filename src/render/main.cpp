#include <SDL.h>
#include <GL/gl.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


#include <object.h>
#include <sdl.h>
#include <controls.h>
#include <material.h>
#include <models.h>
#include <general_def.h>
#include <scene.h>
#include <vector.h>
#include <font.h>
#include <light.h>
#include <settings.h>

#ifdef _WIN32
#undef main
#endif

#include <iostream>
#include <ostream>

Settings *gameSettings;
Scene *mainScene;

bool printFPS = false;
bool render = true;


using namespace std;




int main(int argc, char *argv[]){

    gameSettings = new Settings("settings");
    //Create Window and Scene
    SDL mainwindow = SDL(gameSettings->width,gameSettings->height,gameSettings->sdlFlags,"Cryolite Engine");
    mainScene = new Scene();

    // Create camera, Global light and Input controler
    Camera *Player = new Camera(vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,gameSettings->fov,0,0,gameSettings->height,gameSettings->width);
    mainScene->Camlist->ListPushFront(Player);
    Controls playerControls = Controls(&mainwindow);
    mainScene->GlobalAmbience = new GlobalLight();

    // Draw test models
    INIT_Models(mainScene);

    //GL Settigs
    glMatrixMode( GL_PROJECTION );
    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_COLOR_MATERIAL);
    glLineWidth(gameSettings->lineWidth);
    glPointSize(gameSettings->pointSize);

    // Skysphere
    GLUquadric *q =gluNewQuadric();
    gluQuadricTexture(q, true);
    Material *sky = new Material(IMAGE(sky1.jpg));

    //Background Music
    Mix_Music *music = Mix_LoadMUS(SOUND(moon.mp3));
    if(music==NULL)
        printf("could not load music!!!\n");
    Mix_PlayMusic( music, -1 );

    float lastFPS = 0;
    mainScene->lasttick = SDL_GetTicks();


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

        glMatrixMode(GL_MODELVIEW);

        playerControls.controls_handler(Player);


        glBindTexture( GL_TEXTURE_2D, 0);

        mainScene->render();


        glPushMatrix();
        glTranslatef(Player->position.x,Player->position.y,Player->position.z);
        glRotated(90,1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBindTexture( GL_TEXTURE_2D, sky->textureGL);
        gluSphere(q,50,100,100);
        glPopMatrix();



        drawHUD();

        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffer
    }

    return 0;
}
