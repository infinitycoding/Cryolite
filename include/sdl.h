#ifndef CRYOLITE_SDL_H
#define CRYOLITE_SDL_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <List.h>

struct usedHandles
{
    bool KeyUp;
    bool KeyDown;
    bool MouseButtonUp;
    bool MouseButtonDown;
    bool MouseMotion;
    bool MouseWheel;
    bool Quit;
};


class EventHandle
{
    public:

        usedHandles types;
        EventHandle *object;


        virtual void handleKeyDown(SDL_KeyboardEvent *e);
        virtual void handleKeyUp(SDL_KeyboardEvent *e);
        virtual void handleMouseButtonUp(SDL_MouseButtonEvent *e);
        virtual void handleMouseButtonDown(SDL_MouseButtonEvent *e);
        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);
        //virtual void handleMouseWheel(SDL_MouseWheelEvent *e);
        virtual void handleQuit();

        EventHandle();
        virtual ~EventHandle();
};


class SDL
{
    public:

        SDL(int width, int height, int flags, const char* caption);
        ~SDL();

        void addHandle(EventHandle *Instance);
        int  removeHandle(EventHandle *Instance);
        void pollEvents();
        static void SDLexit();

    private:
        List<EventHandle> *events;
        SDL_Surface *screen;
        bool lock;
};






#endif
