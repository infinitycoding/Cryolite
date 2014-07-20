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

#include <util/settings.h>



using namespace std;



bool Settings::loadSettingsFile(const char *filename)
{
    return true;
}


void Settings::activateSettings()
{

}


void Settings::initSettings()
{

}





EngineSettings::EngineSettings()
{
    initSettings();
}


EngineSettings::EngineSettings(const char *filename)
{
    initSettings();

    loadSettingsFile(filename);
}


EngineSettings::~EngineSettings()
{

}


bool EngineSettings::loadSettingsFile(const char *filename)
{
    Script settingsscript = Script(filename);

    if(!settingsscript.run())
        return false;

    captureMouse = settingsscript.getGlobalBool("catchCourser");
    if(captureMouse)
        sdlFlags |= SDL_WINDOW_INPUT_GRABBED;

    hud = settingsscript.getGlobalBool("drawHUD");
    if(settingsscript.getGlobalBool("fullscreen")) sdlFlags |= SDL_WINDOW_FULLSCREEN;
    width = settingsscript.getGlobalNumber("width");
    height = settingsscript.getGlobalNumber("height");
    multisamples = settingsscript.getGlobalNumber("multisamples");
    lineWidth = settingsscript.getGlobalNumber("linewidth");
    pointSize = settingsscript.getGlobalNumber("pointsize");
    fov = settingsscript.getGlobalNumber("fov");

    return true;
}


void EngineSettings::activateSettings()
{
    glLineWidth(lineWidth);
    glPointSize(pointSize);

    if(captureMouse)
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
    else
    {
        SDL_ShowCursor(SDL_ENABLE);
    }
}


void EngineSettings::initSettings()
{
    captureMouse = true;
    hud = true;
    width = 640;
    height = 480;
    sdlFlags = SDL_WINDOW_OPENGL;
    multisamples = 4;
    lineWidth = 1;
    pointSize = 1;
    fov = 80;
}
