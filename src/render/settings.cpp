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


void Settings::getValueString(const char *line, char *string)
{
    int i, j;

    for(i = 0; line[i] != '='; i++);
    for(i++; line[i] == ' '; i++);

    for(j = 0; line[i] != '\0' && line[i] != '\n'; i++, j++)
        string[j] = line[i];
}


float Settings::getValueFloat(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);
    return atof(string);
}


int Settings::getValueInt(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);
    return atoi(string);
}


bool Settings::getValueBool(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);

    if((strncmp(string, "enable", 6) == 0) || (strncmp(string, "on", 2) == 0) || (strncmp(string, "yes", 3) == 0) || (strncmp(string, "activate", 8) == 0) || (strncmp(string, "true", 4) == 0) || (strncmp(string, "1", 1) == 0))
        return true;
    else if((strncmp(string, "disable", 7) == 0) || (strncmp(string, "off", 3) == 0) || (strncmp(string, "no", 2) == 0) || (strncmp(string, "deactivate", 10) == 0) || (strncmp(string, "false", 5) == 0) || (strncmp(string, "0", 1) == 0))
        return false;
    else
    {
        cout << "The settings-file is corrupted." << endl;
        cout << "The incorrect line is the following one:" << endl;
        cout << line << endl;
        return false;
    }
}

