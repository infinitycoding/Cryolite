#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED



#include <GL/gl.h>
#include <SDL.h>


#include <parser.h>
#include <general_def.h>



class Settings : public ExtParser
{
    public:
        virtual bool loadSettingsFile(const char *filename);
        virtual void activateSettings();

    protected:
        virtual void initSettings();
};


class EngineSettings : public Settings
{
    public:
        EngineSettings();
        EngineSettings(const char *filename);
        virtual ~EngineSettings();

        virtual bool loadSettingsFile(const char *filename);
        virtual void activateSettings();


        bool captureMouse;
        bool hud;
        int width;
        int height;
        int sdlFlags;
        int multisamples;
        int FPSAccuracy;
        float lineWidth;
        float pointSize;
        float fov;

    protected:
        virtual void initSettings();
};


#endif
