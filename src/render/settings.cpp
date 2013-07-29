#include <settings.h>



using namespace std;



Settings::Settings()
{
    initSettings();
}


Settings::Settings(const char *filename)
{
    initSettings();

    loadSettingsFile(filename);
}


Settings::~Settings()
{

}


bool Settings::loadSettingsFile(const char *filename)
{
    FILE *f;
    char line[MAX_LINELENGTH];

    if((f = fopen(filename, "r")) == NULL)
        return false;

    do
    {
        fgets(line, MAX_LINELENGTH, f);

        if(strncmp(line, "width", 5) == 0)
        {
            width = getValueInt(line);
        }
        else if(strncmp(line, "height", 6) == 0)
        {
            height = getValueInt(line);
        }
        else if(strncmp(line, "fullscreen", 10) == 0)
        {
            if(getValueBool(line) == true)
                sdlFlags |= SDL_FULLSCREEN;
        }
        else if(strncmp(line, "catchCourser", 12) == 0)
        {
            captureMouse = getValueBool(line);
        }
        else if(strncmp(line, "multisamples", 12) == 0)
        {
            multisamples = getValueInt(line);
        }
        else if(strncmp(line, "linewidth", 9) == 0)
        {
            lineWidth = getValueFloat(line);
        }
        else if(strncmp(line, "pointsize", 9) == 0)
        {
            pointSize = getValueFloat(line);
        }
        else if(strncmp(line, "fov", 3) == 0)
        {
            fov = getValueFloat(line);
        }

    }while(!feof(f));

    if(fclose(f) == 0)
        return false;

    return true;
}


void Settings::activateSettings()
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


void Settings::initSettings()
{
    captureMouse = true;
    width = 640;
    height = 480;
    sdlFlags = SDL_OPENGL|SDL_HWSURFACE;
    multisamples = 4;
    lineWidth = 1;
    pointSize = 1;
    fov = 80;
}

