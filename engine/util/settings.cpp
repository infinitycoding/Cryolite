#include <settings.h>



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
    hud = settingsscript.getGlobalBool("drawHUD");
    if(settingsscript.getGlobalBool("fullscreen")) sdlFlags |= SDL_FULLSCREEN;
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
        SDL_WM_GrabInput( SDL_GRAB_ON );
    }
    else
    {
        SDL_ShowCursor(SDL_ENABLE);
        SDL_WM_GrabInput( SDL_GRAB_OFF );
    }
}


void EngineSettings::initSettings()
{
    captureMouse = true;
    hud = true;
    width = 640;
    height = 480;
    sdlFlags = SDL_OPENGL|SDL_HWSURFACE;
    multisamples = 4;
    lineWidth = 1;
    pointSize = 1;
    fov = 80;
}

