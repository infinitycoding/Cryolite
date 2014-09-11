#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED



#include <camera.h>
#include <level.h>



struct Viewport
{
    int x;
    int y;
    int width;
    int height;
    Camera *cam;
    Level *lvl;
};


class Render
{
    public:
        static void render(Viewport *view);

    protected:
        static void renderPolygones(Object *currentObject);
        static void resetLights(Viewport *view);
};


#endif
