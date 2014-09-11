/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.

     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.

     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <util/glew.h>
#include <mediaLayer.h>
#include <controls.h>
#include <models.h>
#include <util/general_def.h>
#include <font.h>
#include <level.h>
#include <light.h>
#include <util/settings.h>
#include <util/script.h>
#include <util/vector.h>
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
    Camera *Player = new Camera(NULL, vector(STARTING_X,STARTING_Y,STARTING_Z),vector(0,0,1),STANDART_NEARCLIP,STANDART_FARCLIP,engineSettings.fov);
    mainLevel->addCam(Player);

    Viewport *gameView = new Viewport;
    gameView->x = 0; gameView->y = 0; gameView->height = 480; gameView->width = 640;
    gameView->lvl = mainLevel; gameView->cam = Player;
    mainwindow->addViewport(gameView);

    Lamp *Sun = new Lamp();
    Sun->setDiffuseLight(10, 1, 0, 1.0);
    Sun->setPosition(vector(0,0,80));
    Sun->setQuadAttenaution(0.001);

    Sun->directed(true);

    Sun->activate();
    mainLevel->addLamp(Sun);

    INIT_Models(mainLevel);

    Sun->setRelation(iccube);

    Controls playerControls = Controls(mainwindow, &engineSettings);

    mainLevel->GlobalAmbience = new GlobalLight(0.6,0.6,0.6,1);

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



    engineSettings.activateSettings();

    // Skysphere
    GLUquadric *q =gluNewQuadric();
    gluQuadricTexture(q, true);
    Texture *sky = Material::TexCache->requestTexture(IMAGE(sky1.jpg));
    alDistanceModel( AL_LINEAR_DISTANCE );


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
    }

    return 0;
}
