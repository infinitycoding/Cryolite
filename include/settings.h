#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED



#include <GL/gl.h>
#include <SDL.h>

#include <iostream>
#include <string.h>


#include <general_def.h>



#define MAX_LINELENGTH 30




class Settings
{
    public:
        Settings();
        Settings(const char *filename);
        virtual ~Settings();

        bool loadSettingsFile(const char *filename);
        void activateSettings();


        bool captureMouse;
        int width;
        int height;
        int sdlFlags;
        int multisamples;
        float lineWidth;
        float pointSize;
        float fov;

    private:
        void initSettings();

        void getValueString(const char *line, char *string);
        float getValueFloat(const char *line);
        int getValueInt(const char *line);
        bool getValueBool(const char *line);

};


#endif
