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

#include <SDL_image.h>
#include <iostream>

#ifdef _WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#define ON_WINDOWS true
#endif
#ifndef _WIN32
#define ON_WINDOWS false
#endif

using namespace std;

bool sdlInitiaed = false;
bool audioInitiaed = false;

/**
 * @brief Creates a new Window with independent Evenent and audio handling.
 * @param width Width of the new window.
 * @param height Height of the new window.
 * @param flags The flags for the SDL-Screen
 * @param caption The capton of the new window.
 * @param multisamples The optional Multisample level
 */
MediaLayer::MediaLayer(int width, int height, int flags, const char* caption, int multisamples = 0)
{
    this->screen = NULL;
    this->width = width;
    this->height = height;
    // initiate SDL
    if(!sdlInitiaed)
    {
        sdlInitiaed = true;
        if(SDL_Init( SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
        {
            cerr<<"Video initialization failed: "<<SDL_GetError()<<endl;
            exit(-1);
        }

        atexit(MediaLayer::MediaExit); // Quit SDL if the programm ends.
    }
    // initiate SDL_Mixer
    if(!audioInitiaed)
    {
        audioInitiaed = true;
        if(Mix_OpenAudio(AUDIORATE, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
        {
            cerr<<"SDL Mixer initialization failed: "<<Mix_GetError()<<endl;
            exit(-1);
        }
    }


    screen = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderContext =  SDL_GL_CreateContext(screen);



    if(flags & SDL_WINDOW_OPENGL)
    {
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisamples);
    }


    if( this->screen == NULL ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(-1);
    }

    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    this->events = new List<EventHandle>;

    defaultKeyboard = new InputDevice;
    defaultKeyboard->id = 0;
    defaultKeyboard->name = "default keyboard";
    defaultKeyboard->type = keyboard;

    defaultMouse = new InputDevice;
    defaultMouse->id = 0;
    defaultMouse->name = "default mouse";
    defaultMouse->type = mouse;


    joysticks = new List<InputDevice>;
    gamecontrollers = new List<InputDevice>;

    int numOfJoysticks = SDL_NumJoysticks();

    for(int i = 0; i < numOfJoysticks; i++)
    {
        if(SDL_IsGameController(i))
        {
            SDL_GameController *controller = SDL_GameControllerOpen(i);
            if(controller)
            {
                InputDevice *device = new InputDevice;
                device->id = i;
                device->type = gamecontroller;
                device->name = SDL_GameControllerName(controller);
                SDL_GameControllerEventState(SDL_ENABLE);
                gamecontrollers->PushFront(device);
            }
            else
            {
                fprintf(stderr,"Could not open game controller %d : %s\n", i, SDL_GetError());
            }
        }
        else
        {
            SDL_Joystick *controller = SDL_JoystickOpen(i);
            if(controller)
            {
                InputDevice *device = new InputDevice;
                device->id = i;
                device->type = joystick;
                device->name = SDL_JoystickName(controller);
                SDL_JoystickEventState(SDL_ENABLE);
                joysticks->PushFront(device);
                printf("joystick %d found!\n", device->id);
            }
            else
            {
                fprintf(stderr,"Could not open joystick %d : %s\n", i, SDL_GetError());
            }

        }
    }
}

/**
 * @brief Destroys a MediaLayer
 */
MediaLayer::~MediaLayer()
{

    alcDestroyContext(context);
    alcCloseDevice(device);
    delete events;
    SDL_DestroyWindow(this->screen);
    delete defaultKeyboard;
    delete defaultMouse;
    delete joysticks;
    delete gamecontrollers;
}

/**
 * @brief Adds a EventHandle to the current MediaLayer.
 * @param Instance A pointer to a EventHandle Instance
 */
void MediaLayer::addHandle(EventHandle *Instance)
{
    this->events->PushFront(Instance);
}

/**
 * @brief Removes a EventHandle from the the current MediaLayer.
 * @param Instance A pointer to a EventHandle Instance
 */
int MediaLayer::removeHandle(EventHandle *Instance)
{
    ListIterator<EventHandle> E = ListIterator<EventHandle>(events);
    E.SetFirst();
    while(!E.IsLast())
    {
        EventHandle* currentHandler = E.GetCurrent();
        if(currentHandler == Instance)
        {
            E.Remove();
        }
        else
        {
            E.Next();
        }

    }
    return 0;
}

/**
 * @brief Handles all events occured since the last call and redirects them to ther handling instance.
 */
void MediaLayer::pollEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(events)
        {
            ListIterator<EventHandle> E = ListIterator<EventHandle>(events);
            E.SetFirst();
            while(!E.IsLast())
            {
                ListIterator<InputDevice> ig = ListIterator<InputDevice>(gamecontrollers);
                ListIterator<InputDevice> ij = ListIterator<InputDevice>(joysticks);
                EventHandle* currentEvent = (EventHandle*) E.GetCurrent();
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        currentEvent->handleButtonDown(defaultKeyboard, event.key.timestamp, event.key.keysym.scancode);
                        break;
                    case SDL_KEYUP:
                        currentEvent->handleButtonUp(defaultKeyboard, event.key.timestamp, event.key.keysym.scancode);
                        break;
                    case SDL_TEXTINPUT:
                        currentEvent->handleTextInput(&event.text);
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        currentEvent->handleButtonDown(defaultMouse, event.button.timestamp, event.button.button);
                        break;
                    case  SDL_MOUSEBUTTONUP:
                        currentEvent->handleButtonUp(defaultMouse, event.button.timestamp, event.button.button);
                        break;
                    case SDL_MOUSEMOTION:
                        currentEvent->handleMouseMotion(&event.motion);
                        break;
                    case SDL_MOUSEWHEEL:
                        currentEvent->handleMouseWheel(&event.wheel);
                        break;

                    case SDL_CONTROLLERDEVICEADDED:
                        currentEvent->handleControllerDeviceAdded(&event.cdevice);
                        break;
                    case SDL_CONTROLLERDEVICEREMOVED:
                        currentEvent->handleControllerDeviceRemoved(&event.cdevice);
                        break;
                    case SDL_CONTROLLERDEVICEREMAPPED:
                        currentEvent->handleControllerDeviceRemapped(&event.cdevice);
                        break;
                    case SDL_CONTROLLERBUTTONDOWN:;
                        ig.SetFirst();
                        while(!ig.IsLast() && ig.GetCurrent()->id != event.cbutton.which) ig.Next();
                        if(ig.IsLast())
                            fprintf(stderr,"Signal from unregisterd game controller %d\n", event.cbutton.which);
                        currentEvent->handleButtonDown(ig.GetCurrent(), event.cbutton.timestamp, event.cbutton.button);
                        break;
                    case SDL_CONTROLLERBUTTONUP:
                        ig.SetFirst();
                        while(!ig.IsLast() && ig.GetCurrent()->id != event.cbutton.which) ig.Next();
                        if(ig.IsLast())
                            fprintf(stderr,"Signal from unregisterd game controller %d\n", event.cbutton.which);
                        currentEvent->handleButtonUp(ig.GetCurrent(), event.cbutton.timestamp, event.cbutton.button);
                        break;
                    case SDL_CONTROLLERAXISMOTION:
                        currentEvent->handleControllerAxis(&event.caxis);
                        break;

                    case SDL_JOYAXISMOTION:
                        currentEvent->handleJoystickAxis(&event.jaxis);
                        break;
                    case SDL_JOYBALLMOTION:
                        currentEvent->handleJoystickBall(&event.jball);
                        break;
                    case SDL_JOYHATMOTION:
                        currentEvent->handleJoystickHat(&event.jhat);
                        break;
                    case SDL_JOYBUTTONUP:
                        ij.SetFirst();
                        while(!ij.IsLast() && ij.GetCurrent()->id != event.jbutton.which) ij.Next();
                        if(ij.IsLast())
                            fprintf(stderr,"Signal from unregisterd joystick %d\n", event.jbutton.which);
                        currentEvent->handleButtonUp(ij.GetCurrent(), event.jbutton.timestamp, event.jbutton.button);
                        break;
                    case SDL_JOYBUTTONDOWN:
                        ij.SetFirst();
                        while(!ij.IsLast() && ij.GetCurrent()->id != event.jbutton.which) ij.Next();
                        if(ij.IsLast())
                            fprintf(stderr,"Signal from unregisterd joystick %d\n", event.jbutton.which);
                        currentEvent->handleButtonDown(ij.GetCurrent(), event.jbutton.timestamp, event.jbutton.button);
                        break;
                    case SDL_JOYDEVICEADDED:
                        currentEvent->handleJoystickDeviceAdded(&event.jdevice);
                        break;
                    case SDL_JOYDEVICEREMOVED:
                        currentEvent->handleJoystickDeviceRemoved(&event.jdevice);
                        break;

                    case SDL_FINGERUP:
                        currentEvent->handleTouchUp(&event.tfinger);
                        break;
                    case SDL_FINGERDOWN:
                        currentEvent->handleTouchDown(&event.tfinger);
                        break;
                    case SDL_FINGERMOTION:
                        currentEvent->handleTouchMotion(&event.tfinger);
                        break;

                    case SDL_WINDOWEVENT:
                        currentEvent->handleWindow(&event.window);
                        break;

                    case SDL_QUIT:
                        currentEvent->handleQuit();
                        break;
                };

                E.Next();
            }

        }
    }
}

GLuint MediaLayer::loadTexture(const char *filename)
{
    return loadTexture(filename,GL_NEAREST,GL_NEAREST);
}

GLuint MediaLayer::loadTexture(const char *filename,GLenum MinFilter,GLenum MagFilter)
{
    GLint nOfColors = 0;
    GLenum texture_format = 0;
    SDL_Surface *SDL_Texture = IMG_Load(filename);
    GLuint GL_Texture = 0;

    if(SDL_Texture == NULL)
    {
        printf("textur %s not found\n",filename);
        return 0;
    }


    nOfColors = SDL_Texture->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (SDL_Texture->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (SDL_Texture->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        fprintf(stderr,"warning: %s is not truecolor.. this will probably break\n", filename);
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &GL_Texture );
    #ifndef _WIN32
    glActiveTexture(GL_Texture);
    #endif
    glBindTexture( GL_TEXTURE_2D, GL_Texture );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, SDL_Texture->w, SDL_Texture->h, 0,texture_format, GL_UNSIGNED_BYTE, SDL_Texture->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter );


    cout << "texur " << GL_Texture << " " << filename << " loaded" << endl;

    SDL_FreeSurface(SDL_Texture);
    return GL_Texture;
}

GLuint MediaLayer::surfToTexture(SDL_Surface *surf){return surfToTexture(surf,GL_NEAREST,GL_NEAREST);}

GLuint MediaLayer::surfToTexture(SDL_Surface *surf,GLenum MinFilter,GLenum MagFilter)
{

    GLint nOfColors = 0;
    GLenum texture_format = 0;
    GLuint GL_Texture = 0;

    if(surf == NULL)
    {
        cerr<<"texture pointer is NULL. Returned NULL texture"<<endl;
        return 0;
    }


    nOfColors = surf->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (surf->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (surf->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        cerr<<"warning: surface is not a truecolor surface .. this will probably break"<<endl;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &GL_Texture );
    #ifndef _WIN32
    glActiveTexture(GL_Texture);
    #endif
    glBindTexture( GL_TEXTURE_2D, GL_Texture );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surf->w, surf->h, 0,texture_format, GL_UNSIGNED_BYTE, surf->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter );

    return GL_Texture;
}

ALuint MediaLayer::chunkToBuffer(Mix_Chunk *sound)
{
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, sound->abuf, sound->alen, 44100);
    return buffer;
}


void MediaLayer::MediaExit()
{
    SDL_Quit();
    Mix_CloseAudio();
    printf("Application closed \n");
}


EventHandle::EventHandle()  {}
EventHandle::~EventHandle() {}



void EventHandle::handleButtonUp(InputDevice *device, uint32_t timestamp, scancode_t scancode)     {}
void EventHandle::handleButtonDown(InputDevice *device, uint32_t timestamp, scancode_t scancode)   {}

void EventHandle::handleMouseMotion(SDL_MouseMotionEvent *e)                    {}
void EventHandle::handleMouseWheel(SDL_MouseWheelEvent *e)                      {}

void EventHandle::handleControllerDeviceAdded(SDL_ControllerDeviceEvent *e)     {}
void EventHandle::handleControllerDeviceRemoved(SDL_ControllerDeviceEvent *e)   {}
void EventHandle::handleControllerDeviceRemapped(SDL_ControllerDeviceEvent *e)  {}
void EventHandle::handleControllerAxis(SDL_ControllerAxisEvent *e)              {}

void EventHandle::handleJoystickAxis(SDL_JoyAxisEvent *e)                       {}
void EventHandle::handleJoystickBall(SDL_JoyBallEvent *e)                       {}
void EventHandle::handleJoystickHat(SDL_JoyHatEvent *e)                         {}
void EventHandle::handleJoystickDeviceAdded(SDL_JoyDeviceEvent *e)              {}
void EventHandle::handleJoystickDeviceRemoved(SDL_JoyDeviceEvent *e)            {}

void EventHandle::handleTouchUp(SDL_TouchFingerEvent *e)                        {}
void EventHandle::handleTouchDown(SDL_TouchFingerEvent *e)                      {}
void EventHandle::handleTouchMotion(SDL_TouchFingerEvent *e)                    {}

void EventHandle::handleWindow(SDL_WindowEvent *e)                              {}

void EventHandle::handleTextInput(SDL_TextInputEvent *e)                        {}

void EventHandle::handleQuit()                                                  {}



