#include <glew.h>

#include <SDL.h>
#include <GL/gl.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/glu.h>

#include <SDL_thread.h>
#include <SDL_mixer.h>

#include <mediaLayer.h>
#include <controls.h>
#include <models.h>
#include <general_def.h>
#include <font.h>
#include <level.h>
#include <light.h>
#include <settings.h>
#include <lua/script.h>
#include <vector.h>
#include <hud.h>
#include <screen.h>

#ifdef _WIN32
#undef main
#endif

Level *mainLevel;

bool printFPS = false;
bool render = true;


using namespace std;

extern Object *iccube;

//GLfloat fogcolor[4] = {0.5,0.5,0.5,1};

int main(int argc, char *argv[]){
    EngineSettings engineSettings = EngineSettings("game/scripts/settings.lua");
    //Create Window and Scene
    Screen *mainwindow = new Screen(engineSettings.width,engineSettings.height,engineSettings.sdlFlags,"Cryolite Engine",engineSettings.multisamples);
    mainLevel = new Level();
    mainwindow->addLevel(mainLevel);

    GLEW ew;

    if(ew.loadingSuccess() == GLEW_OK)
    {
        printf("Using GLEW %s\n", ew.getVersion());

        if(ew.checkExtention("GL_ARB_texture_compression")) printf("ARB_texture_compression: supported\n"); else printf("ARB_texture_compression: unsupported\n");
    }
    else
    {
        printf("Loading GLEW failed.\n");
    }

    // Create camera, Global light and Input controler
    Camera *Player = new Camera(NULL, vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,engineSettings.fov,0,0,engineSettings.height,engineSettings.width);
    mainLevel->addCam(Player);

    Lamp *Sun = new Lamp();
    Sun->setDiffuseLight(10, 1, 0, 1.0);
    Sun->setPosition(vector(0,0,80));
    Sun->setQuadAttenaution(0.001);

    Sun->directed(true);

    Sun->activate();
    mainLevel->addLamp(Sun);


    /*Lamp *Spot = new Lamp();
    Spot->setDiffuseLight(10, 0, 0, 1.0);
    Spot->setPosition(vector(0,10,0));
    //Spot->setCutOf(90);
    Spot->setQuadAttenaution(0.001);

    Spot->directed(true);

    Spot->activate();
    mainScene->addLamp(Spot);*/

    INIT_Models(mainLevel);

    Sun->setRelation(iccube);

    Controls playerControls = Controls(mainwindow, &engineSettings);

    mainLevel->GlobalAmbience = new GlobalLight(0.3,0.3,0.3,1);

    //GL Settigs
    glMatrixMode( GL_PROJECTION );
    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_TEXTURE_2D );
    glEnable(0x809D);//GL_MULTISAMPLE_ARB
    glEnable(GL_COLOR_MATERIAL);

    /*glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogcolor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, 0.05);
    glFogf(GL_FOG_START, 40);
    glFogf(GL_FOG_END, 50);*/




    engineSettings.activateSettings();

    // Skysphere
    GLUquadric *q =gluNewQuadric();
    gluQuadricTexture(q, true);
    Texture *sky = Material::TexCache->requestTexture(IMAGE(sky1.jpg));
    alDistanceModel( AL_LINEAR_DISTANCE );

    /*HUD testHUD;
    testHUD.addElement((engineSettings.width / 2) - 50, (engineSettings.height / 2) - 50, 100, 100, IMAGE(aim.png));
    testHUD.addElement(engineSettings.width-((engineSettings.width/100)*HOR)-10, engineSettings.height-((engineSettings.height/100)*VERT)-10, ((engineSettings.width/100)*HOR), ((engineSettings.height/100)*VERT), IMAGE(man.png));*/

    HUD testHUD("game/scripts/hud.lua", engineSettings.width, engineSettings.height);

    //Shader testShader = Shader(SHADER(basicvert.glsl), SHADER(basicfrag.glsl));
    //testShader.activate();
    Script testScript(SCRIPT(testscript.lua));
    testScript.run();

    if(engineSettings.hud)
        mainwindow->addHUD(&testHUD);


    while(render){ //render
        if(printFPS)
            mainLevel->fps->print();

        mainwindow->handleEvents(); // Eventhandler

        glMatrixMode(GL_MODELVIEW);


        playerControls.controls_handler(Player);


        glBindTexture( GL_TEXTURE_2D, 0);


        mainwindow->render();

        SDL_GL_SwapBuffers(); // Changes frontbuffer and backbuffer
    }

    return 0;
}
