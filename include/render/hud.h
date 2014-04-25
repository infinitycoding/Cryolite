#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED



#include <vertex.h>
#include <List.h>
#include <sdl.h>

#include <SDL.h>
#include <GL/gl.h>



enum renderSource
{
    renderSDL, renderGL, renderNOT
};



class HUD_Element
{
    public:
        HUD_Element();  // zero constructor
        HUD_Element(vertex2D pos, float w, float h, GLuint tex, SDL_Surface *c, renderSource s);
        HUD_Element(HUD_Element *templateElement);

        void renderElement();
        void renderElement(renderSource type);


        vertex2D position;
        float width;
        float height;
        GLuint gltex;
        SDL_Surface *content;
        renderSource source;
};


class HUD
{
    public:
        HUD();                      // zero constructor
        HUD(const char *script);    // standart constructor, loads hud elements out of a lua script
        HUD(HUD *templateHUD);      // copy constructor, no idea why

        void addElement(HUD_Element *newElement);
        void renderElement(HUD_Element *element);
        void render(int swidth, int sheight);


        List<HUD_Element> *elements;
};



#endif // HUD_H_INCLUDED
