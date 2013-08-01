#include <SDL.h>
#include <GL/gl.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/glu.h>

#include <SDL_thread.h>
#include <SDL_mixer.h>


#include <sdl.h>
#include <controls.h>
#include <models.h>
#include <general_def.h>
#include <scene.h>
#include <font.h>
#include <level.h>
#include <light.h>
#include <settings.h>
#include <sound.h>
#include <luaWrapper.h>

#ifdef DEBUG
#include <profiler.h>
#endif

#ifdef _WIN32
#undef main
#endif

Settings *gameSettings;
Scene *mainScene;

bool printFPS = false;
bool render = true;


using namespace std;

extern Sound *shotSound;
extern Object *iccube;
extern Object *gravelcube;




int main(int argc, char *argv[]){
    LUASkript testSkript = LUASkript(SKRIPT(testscript.lua));
    testSkript.insertDoubleVar("cppvar", 5.5);
    testSkript.runSkript();
    double luavar = testSkript.getDoubleVar("luavar");
    cout << "luavar = " << luavar << endl;

    cout << endl;

    gameSettings = new Settings("settings");
    //Create Window and Scene
    SDL mainwindow = SDL(gameSettings->width,gameSettings->height,gameSettings->sdlFlags,"Cryolite Engine");
    mainScene = new Scene();

    // Create camera, Global light and Input controler
    Camera *Player = new Camera(NULL, vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,gameSettings->fov,0,0,gameSettings->height,gameSettings->width);
    mainScene->addCam(Player);

    Lamp *Sun = new Lamp();
    Sun->setDiffuseLight(10, 0, 0, 1.0);
    Sun->setPosition(vector(0,0,0));

    Sun->activate();
    mainScene->addLamp(Sun);


    Controls playerControls = Controls(&mainwindow);
    mainScene->GlobalAmbience = new GlobalLight(0.5,0.5,0.5,1);

    // Draw test models
    INIT_Models(mainScene);

    gravelcube->relativeToObject = iccube;

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




    gameSettings->activateSettings();

    // Skysphere
    GLUquadric *q =gluNewQuadric();
    gluQuadricTexture(q, true);
    Texture *sky = Material::TexCache->requestTexture(IMAGE(sky1.jpg));

    Level testLevel = Level();

    alDistanceModel( AL_LINEAR_DISTANCE );



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

        testLevel.refreshBackgroundMusic(Player->getPosition());

        mainwindow.pollEvents();    // Eventhandler

        glMatrixMode(GL_MODELVIEW);

        playerControls.controls_handler(Player);



        glBindTexture( GL_TEXTURE_2D, 0);


        mainScene->render();
        shotSound->refreshPosition(Player->getPosition(),iccube->getPosition());



        glPushMatrix();
        glTranslatef(Player->getPosition().x,Player->getPosition().y,Player->getPosition().z);
        glRotated(90,1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBindTexture( GL_TEXTURE_2D, sky->nr);
        gluSphere(q,50,100,100);
        glPopMatrix();






        drawHUD();

        SDL_GL_SwapBuffers();   // Changes frontbuffer and backbuffer
    }

    return 0;
}
