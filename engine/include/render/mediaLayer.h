#ifndef CRYOLITE_SDL_H
#define CRYOLITE_SDL_H
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


#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>

#include <util/List.h>

#define AUDIORATE 22050


class EventHandle
{
    public:
        virtual void handleKeyDown(SDL_KeyboardEvent *e);
        virtual void handleKeyUp(SDL_KeyboardEvent *e);
        virtual void handleMouseButtonUp(SDL_MouseButtonEvent *e);
        virtual void handleMouseButtonDown(SDL_MouseButtonEvent *e);
        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);
        virtual void handleMouseWheel(SDL_MouseWheelEvent *e);
        virtual void handleControllerDeviceAdded(SDL_ControllerDeviceEvent *e);
        virtual void handleControllerDeviceRemoved(SDL_ControllerDeviceEvent *e);
        virtual void handleControllerDeviceRemapped(SDL_ControllerDeviceEvent *e);
        virtual void handleControllerButtonUp(SDL_ControllerButtonEvent *e);
        virtual void handleControllerButtonDown(SDL_ControllerButtonEvent *e);
        virtual void handleControllerAxis(SDL_ControllerAxisEvent *e);
        virtual void handleJoystickAxis(SDL_JoyAxisEvent *e);
        virtual void handleJoystickBall(SDL_JoyBallEvent *e);
        virtual void handleJoystickHat(SDL_JoyHatEvent *e);
        virtual void handleJoystickButtonUp(SDL_JoyButtonEvent *e);
        virtual void handleJoystickButtonDown(SDL_JoyButtonEvent *e);
        virtual void handleJoystickDeviceAdded(SDL_JoyDeviceEvent *e);
        virtual void handleJoystickDeviceRemoved(SDL_JoyDeviceEvent *e);
        virtual void handleTouchUp(SDL_TouchFingerEvent *e);
        virtual void handleTouchDown(SDL_TouchFingerEvent *e);
        virtual void handleTouchMotion(SDL_TouchFingerEvent *e);
        virtual void handleWindow(SDL_WindowEvent *e);
        virtual void handleTextInput(SDL_TextInputEvent *e);
        virtual void handleQuit();

        EventHandle();
        virtual ~EventHandle();
};


class MediaLayer
{
    public:

        MediaLayer(int width, int height, int flags, const char* caption, int multisamples);
        ~MediaLayer();
        static GLuint loadTexture(const char *filename);
        static GLuint loadTexture(const char *filename,GLenum MinFilter,GLenum MagFilter);
        static GLuint surfToTexture(SDL_Surface *surf);
        static GLuint surfToTexture(SDL_Surface *surf,GLenum MinFilter,GLenum MagFilter);
        static ALuint chunkToBuffer(Mix_Chunk *sound);

        void addHandle(EventHandle *Instance);
        int  removeHandle(EventHandle *Instance);
        void pollEvents();
        static void MediaExit();

        int getWidth();
        int getHeight();


    protected:
        int width;
        int height;
        ALCdevice* device;
        ALCcontext* context;
        List<EventHandle> *events;
        SDL_Window *screen;
        SDL_GLContext renderContext;
};






#endif
