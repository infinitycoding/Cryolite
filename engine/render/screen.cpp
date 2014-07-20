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
#include <screen.h>

Screen::Screen(unsigned int width, unsigned int height, unsigned int flags,const char *caption, int multisamples) 
    : MediaLayer(width, height, flags, caption, multisamples)
{
    levels = new List<Level>;
    handles = new List<EventHandle>;
    viewports = new List<Viewport>;
    HUDs = new List<HUD>;
}


Screen::~Screen()
{
    delete levels;
    delete handles;
    delete viewports;
    delete HUDs;
}

bool Screen::addLevel(Level *level)
{
    if(levels->alreadyAdded(level))
        return false;
    levels->PushFront(level);
    return true;
}

bool Screen::removeLevel(Level *level)
{
    return levels->Remove(level);
}

void Screen::render()
{
    ListIterator<Level> i = *ListIterator<Level>(levels).SetFirst();
    while(!i.IsLast())
    {
        i.GetCurrent()->render();
        i.Next();
    }
    this->renderHUDs();
    SDL_GL_SwapWindow(this->screen);
}


void Screen::handleEvents()
{
    //todo: handle global events and focus
    pollEvents();
}


bool Screen::addHUD(HUD *hud)
{
    if(HUDs->alreadyAdded(hud))
        return false;
    HUDs->PushFront(hud);
    return true;
}

bool Screen::removeHUD(HUD *hud)
{
    return HUDs->Remove(hud);
}

void Screen::renderHUDs()
{
    ListIterator<HUD> i = *ListIterator<HUD>(HUDs).SetFirst();
    while(!i.IsLast())
    {
        i.GetCurrent()->render(width,height);
        i.Next();
    }
}


bool Screen::addViewport(Viewport *port)
{
    if(viewports->alreadyAdded(port))
        return false;
    viewports->PushFront(port);
    return true;
}

bool Screen::removeViewport(Viewport *port)
{
    return viewports->Remove(port);
}