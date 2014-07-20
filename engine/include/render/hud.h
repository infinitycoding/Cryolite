#ifndef _HUD_H_
#define _HUD_H_
/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <util/List.h>
#include <vertex.h>
#include <mediaLayer.h>
#include <material.h>
#include <util/general_structs.h>
#include <util/script.h>
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
        HUD(const char *script, float w, float h);    // standart constructor, loads hud elements out of a lua script
        HUD(const char *script, vertex2D res);    // standart constructor, with other parameters
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
        void loadHUD(const char *script, vertex2D res);

        Script *genScript;
        List<HUD_Element> *elements;
};



#endif // HUD_H_INCLUDED
