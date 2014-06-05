#ifndef SCREEN_H
#define SCREEN_H

#include <mediaLayer.h>
#include <List.h>
#include <camera.h>
#include <hud.h>
#include <level.h>

class Viewport
{
    int x;
    int y;
    int widht;
    int height;
    Camera *cam;
};


class Screen : MediaLayer
{
    public:
        Screen(unsigned int width, unsigned int height, unsigned int flags, char *caption, int multisamples);
        ~Screen();

        bool addLevel(Level *level);
        bool removeLevel(Level *level);

        void renderLevels();
        void handleEvents();

        bool addHUD(HUD *hud);
        bool removeHUD(HUD *hud);
        void renderHUDs();

        bool addViewport(Viewport *port);
        bool removeViewport(Viewport *port);

        void render();
    
    protected:
        List<Level> *levels;
        List<EventHandle> *handles;
        List<Viewport> *viewports;
        List<HUD> *HUDs;

};





#endif

