#ifndef SCREEN_H
#define SCREEN_H
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


#include <mediaLayer.h>
#include <util/List.h>
#include <camera.h>
#include <hud.h>
#include <level.h>
#include <render.h>


class Screen : public MediaLayer
{
    public:
        Screen(unsigned int width, unsigned int height, unsigned int flags,const char *caption, int multisamples);
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

