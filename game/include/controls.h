#ifndef CONTROLS_H
#define CONTROLS_H
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
#include <camera.h>
#include <util/settings.h>



class Controls : EventHandle
{
    public:
        Controls(Screen *window, EngineSettings *settings);

        void controls_handler(Camera *cam);

        virtual void handleQuit();
        virtual void handleButtonDown(InputDevice *device, uint32_t timestamp, scancode_t scancode);
        virtual void handleButtonUp(InputDevice *device, uint32_t timestamp, scancode_t scancode);
        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);;
        virtual void screenshot(const char* filename, float width, float height);

        virtual bool toggle(bool parameter);

    private:
        void rotation_handler(Camera *cam);
        void move_handler(Camera *cam);
        void shoot_handler(Camera *cam);


        float right_rotation;
        float down_rotation;

        bool move_right;
        bool move_left;
        bool move_foreward;
        bool move_backward;
        bool move_up;
        bool move_down;

        bool fire;

        bool ghost_mode;

        EngineSettings *options;
};



#endif

