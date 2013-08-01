#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED



#include <GL/gl.h>
#include <SDL.h>


#include <parser.h>
#include <general_def.h>



class Settings : public ExtParser
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
};


#endif
