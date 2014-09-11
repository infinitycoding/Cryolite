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


typedef uint32_t scancode_t;
typedef uint32_t deviceId_t;


enum InputDeviceType
{
    keyboard,
    joystick,
    gamecontroller,
    mouse,
    touchscreen
};


struct InputDevice
{
    deviceId_t id;
    const char *name;
    InputDeviceType type;
};


class EventHandle
{
    public:
        virtual void handleDeviceAdded(InputDevice *device, uint32_t timestamp);
        virtual void handleDeviceRemoved(InputDevice *device, uint32_t timestamp);
        virtual void handleButtonUp(InputDevice *device, uint32_t timestamp, scancode_t scancode);
        virtual void handleButtonDown(InputDevice *device, uint32_t timestamp, scancode_t scancode);

        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);
        virtual void handleMouseWheel(SDL_MouseWheelEvent *e);
        virtual void handleControllerDeviceRemapped(SDL_ControllerDeviceEvent *e);
        virtual void handleControllerAxis(SDL_ControllerAxisEvent *e);
        virtual void handleJoystickAxis(SDL_JoyAxisEvent *e);
        virtual void handleJoystickBall(SDL_JoyBallEvent *e);
        virtual void handleJoystickHat(SDL_JoyHatEvent *e);
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
        InputDevice *addInputDevice(List<InputDevice> *lst, deviceId_t id);
        InputDevice *removeInputDevice(List<InputDevice> *lst, deviceId_t id);

        int width;
        int height;
        ALCdevice* device;
        ALCcontext* context;
        List<EventHandle> *events;
        SDL_Window *screen;
        SDL_GLContext renderContext;

        InputDevice *defaultKeyboard;
        InputDevice *defaultMouse;
        List<InputDevice> *joysticks;
        List<InputDevice> *gamecontrollers;
};






#endif
