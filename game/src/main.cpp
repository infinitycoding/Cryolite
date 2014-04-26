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
#include <lua/script.h>
#include <shader.h>
#include <vector.h>
#include <hud.h>
#include <SDL_net.h>
#include <Net.h>

#ifdef _WIN32
#undef main
#endif

Scene *mainScene;

bool printFPS = false;
bool render = true;


using namespace std;

extern Sound *shotSound;
extern Object *iccube;

//GLfloat fogcolor[4] = {0.5,0.5,0.5,1};



int main(int argc, char *argv[]){
    EngineSettings engineSettings = EngineSettings("game/scripts/settings.lua");
    SDLNet_Init();
    //Create Window and Scene
    SDL mainwindow = SDL(engineSettings.width,engineSettings.height,engineSettings.sdlFlags,engineSettings.multisamples,"Cryolite Engine");
    mainScene = new Scene();

    // Create camera, Global light and Input controler
    Camera *Player = new Camera(NULL, vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,engineSettings.fov,0,0,engineSettings.height,engineSettings.width);
    mainScene->addCam(Player);

    Lamp *Sun = new Lamp();
    Sun->setDiffuseLight(10, 1, 0, 1.0);
    Sun->setPosition(vector(0,0,60));
    Sun->setQuadAttenaution(0.001);

    Sun->directed(true);

    Sun->activate();
    mainScene->addLamp(Sun);


    /*Lamp *Spot = new Lamp();
    Spot->setDiffuseLight(10, 0, 0, 1.0);
    Spot->setPosition(vector(0,10,0));
    //Spot->setCutOf(90);
    Spot->setQuadAttenaution(0.001);

    Spot->directed(true);

    Spot->activate();
    mainScene->addLamp(Spot);*/

    INIT_Models(mainScene);

    Controls playerControls = Controls(&mainwindow, &engineSettings);

    mainScene->GlobalAmbience = new GlobalLight(0.3,0.3,0.3,1);

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
    Level testLevel = Level();
    alDistanceModel( AL_LINEAR_DISTANCE );

    HUD testHUD;
    Texture *aim = Material::TexCache->requestTexture(IMAGE(aim.png));
    vertex2D p;
    p.x = (engineSettings.width / 2) - 50;
    p.y = (engineSettings.height / 2) - 50;
    HUD_Element *testHUDElement = new HUD_Element(p, 100, 100, aim, NULL, renderGL);
    testHUD.addElement(testHUDElement);


    //Shader testShader = Shader(SHADER(basicvert.glsl), SHADER(basicfrag.glsl));
    //testShader.activate();
    Script testScript(SCRIPT(testscript.lua));
    testScript.run();

    Net *server = new Net("archx", 9999, "R2D2");

    server->addObject(iccube);

    while(render){ //render
        if(printFPS)
            mainScene->fps->print();

        testLevel.refreshBackgroundMusic(Player->getPosition());

        mainwindow.pollEvents(); // Eventhandler

        glMatrixMode(GL_MODELVIEW);

        vector last = iccube->localPosition;

        playerControls.controls_handler(Player, server);

        if(iccube->localPosition != last)
            server->updateObject(iccube);

        glBindTexture( GL_TEXTURE_2D, 0);

        server->updateScene(mainScene);
        mainScene->listenerPosition = Player->getPosition();
        mainScene->render();

        Object *currentObject = NULL;
        ListIterator<Object> O = *ListIterator<Object>(mainScene->objectList).SetFirst();

        while(!O.IsLast())
        {
            currentObject = O.GetCurrent();

            if(currentObject->getPosition().len() > 100)
            {
                server->deleteObject(currentObject);
                mainScene->removeObject(currentObject);
                delete currentObject;
                break;
            }

            O.Next();
        }


        glPushMatrix();
        glTranslatef(Player->getPosition().x[0],Player->getPosition().x[1],Player->getPosition().x[2]);

        glRotated(90,1,0,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBindTexture( GL_TEXTURE_2D, sky->nr);
        gluSphere(q,50,100,100);
        glPopMatrix();

        if(engineSettings.hud)
        {
            testHUD.render(Player->width, Player->height);
            drawHUD(Player->width, Player->height);
        }

        SDL_GL_SwapBuffers(); // Changes frontbuffer and backbuffer
    }

    delete server;

    return 0;
}
