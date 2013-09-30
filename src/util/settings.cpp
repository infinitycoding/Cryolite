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
    FILE *f;
    char line[MAX_LINELENGTH];
    char *line_ptr;

    memset(line, '\0', sizeof(line));

    if((f = fopen(filename, "r")) == NULL)
        return false;

    while(!feof(f) && strncmp(line, "[EngineSettings]", 15))
        if(fgets(line, MAX_LINELENGTH, f) == NULL)
            break;

    if(feof(f))
    {
        cerr << "warning: could not find \"[EngineSettings]\" in file " << filename << "." << endl;
        fclose(f);
        return false;
    }

    do
    {
        fgets(line, MAX_LINELENGTH, f);

        line_ptr = line;

        skipUntilCharacters(&line_ptr, breakChars);
        skipCharacters(&line_ptr, placeholders);

        if(strncmp(line, "width", 5) == 0)
        {
            width = getInt(&line_ptr, breakChars);
        }
        else if(strncmp(line, "height", 6) == 0)
        {
            height = getInt(&line_ptr, breakChars);
        }
        else if(strncmp(line, "fullscreen", 10) == 0)
        {
            if(getBool(&line_ptr, breakChars) == true)
                sdlFlags |= SDL_FULLSCREEN;
        }
        else if(strncmp(line, "catchCourser", 12) == 0)
        {
            captureMouse = getBool(&line_ptr, breakChars);
        }
        else if(strncmp(line, "drawHUD", 7) == 0)
        {
            hud = getBool(&line_ptr, breakChars);
        }
        else if(strncmp(line, "multisamples", 12) == 0)
        {
            multisamples = getInt(&line_ptr, breakChars);
        }
        else if(strncmp(line, "linewidth", 9) == 0)
        {
            lineWidth = getFloat(&line_ptr, breakChars);
        }
        else if(strncmp(line, "pointsize", 9) == 0)
        {
            pointSize = getFloat(&line_ptr, breakChars);
        }
        else if(strncmp(line, "fov", 3) == 0)
        {
            fov = getFloat(&line_ptr, breakChars);
        }

    }while(!feof(f) && strncmp(line, "[", 1));

    if(fclose(f) == 0)
        return false;

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

