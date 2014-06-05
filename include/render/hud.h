#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED



#include <vertex.h>
#include <List.h>
#include <mediaLayer.h>
#include <material.h>
#include <general_structs.h>

#include <SDL.h>
#include <GL/gl.h>



class HUD_Element
{
    public:
        HUD_Element();  // zero constructor
        HUD_Element(vertex2D pos, float w, float h, Texture *tex);
        HUD_Element(vertex2D pos, float w, float h, const char *texname);
        HUD_Element(float x, float y, float w, float h, Texture *tex);
        HUD_Element(float x, float y, float w, float h, const char *texname);
        HUD_Element(vertex2D pos, vertex2D s, Texture *tex);
        HUD_Element(vertex2D pos, vertex2D s, const char *texname);
        HUD_Element(float x, float y, vertex2D s, Texture *tex);
        HUD_Element(float x, float y, vertex2D s, const char *texname);
        HUD_Element(HUD_Element *templateElement);
        ~HUD_Element();

        success renderElement();
        vertex2D moveTo(vertex2D newPosition);
        vertex2D getPosition();
        vertex2D changeSize(vertex2D newSize);
        vertex2D getSize();
        Texture *changeContent(Texture *tex);
        Texture *changeContent(const char *texname);
        Texture *getContent();

    protected:
        vertex2D position;
        vertex2D size;
        Texture *glcontent;
};


class HUD
{
    public:
        HUD();                      // zero constructor
        HUD(const char *script);    // standart constructor, loads hud elements out of a lua script
        HUD(HUD *templateHUD);      // copy constructor, no idea why
        ~HUD();

        HUD_Element *addElement(HUD_Element *newElement);
        HUD_Element *addElement(vertex2D pos, float w, float h, Texture *tex);
        HUD_Element *addElement(vertex2D pos, float w, float h, const char *texname);
        HUD_Element *addElement(float x, float y, float w, float h, Texture *tex);
        HUD_Element *addElement(float x, float y, float w, float h, const char *texname);
        HUD_Element *addElement(vertex2D pos, vertex2D s, Texture *tex);
        HUD_Element *addElement(vertex2D pos, vertex2D s, const char *texname);
        HUD_Element *addElement(float x, float y, vertex2D s, Texture *tex);
        HUD_Element *addElement(float x, float y, vertex2D s, const char *texname);
        success render(int swidth, int sheight);

    protected:
        List<HUD_Element> *elements;
};



#endif // HUD_H_INCLUDED
