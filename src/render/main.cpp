#include <SDL.h>
#include <GL/gl.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string.h>
#include <SDL_thread.h>
#include <SDL_image.h>



#include <object.h>
#include <sdl.h>
#include <controls.h>
#include <material.h>
#include <models.h>
#include <general_def.h>
#include <scene.h>
#include <vector.h>
#include <font.h>
#include <SDL_mixer.h>
#ifdef _WIN32
#undef main
#endif

Scene *mainScene;

bool printFPS = false;
bool render = true;
float averageFPS = 0;






int main(int argc, char *argv[]){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

    SDL mainwindow = SDL(WIDTH,HEIGHT,SDL_OPENGL|SDL_HWSURFACE,"Cryolite Engine");     // Create the graphics window

     if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) return false;
     if(TTF_Init()) return false;


    mainScene = new Scene();
    Camera *Player = new Camera(vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,FOV,0,0,HEIGHT,WIDTH);
    printf("add cam\n");
    mainScene->Camlist->ListPushFront(Player);

    Controls playerControls = Controls(&mainwindow);
    INIT_Models(mainScene);

    glMatrixMode( GL_PROJECTION );

    //glFrustum( -1.6, 1.6, -1.2, 1.2, STANDART_NEARCLIP, STANDART_FARCLIP );
    //gluPerspective(FOV, WIDTH/HEIGHT, STANDART_NEARCLIP, STANDART_FARCLIP );

    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );

    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glEnable( GL_TEXTURE_2D );

    glEnable(GL_MULTISAMPLE_ARB);

    glLineWidth (LINEWIDTH);


    GLUquadric *q =gluNewQuadric();
    gluQuadricTexture(q, true);

    Material *sky = new Material(IMAGE(sky1.jpg));

    Mix_Music *music = Mix_LoadMUS(SOUND(moon.mp3));
    if(music==NULL)
        printf("could not load music!!!\n");
    Mix_PlayMusic( music, -1 );


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

        playerControls.controls_handler(Player);


        glBindTexture( GL_TEXTURE_2D, 0);
        mainScene->render();


        glPushMatrix();
        glTranslatef(Player->position.elements[0],Player->position.elements[1],Player->position.elements[2]);
        glRotated(90,1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBindTexture( GL_TEXTURE_2D, sky->textureGL);
        gluSphere(q,50,100,100);
        glPopMatrix();



        drawHUD();

        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffera


    }

    TTF_Quit();
    Mix_CloseAudio();

    return 0;

}
