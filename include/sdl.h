#ifndef CRYOLITE_SDL_H
#define CRYOLITE_SDL_H

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>

#include <List.h>

#define AUDIORATE 22050

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
        static GLuint loadTexture(const char *filename);
        static GLuint loadTexture(const char *filename,GLenum MinFilter,GLenum MagFilter);
        static GLuint surfToTexture(SDL_Surface *surf);
        static GLuint surfToTexture(SDL_Surface *surf,GLenum MinFilter,GLenum MagFilter);
        static ALuint chuckToBuffer(Mix_Chunk *sound);

        void addHandle(EventHandle *Instance);
        int  removeHandle(EventHandle *Instance);
        void pollEvents();
        static void SDLexit();

        ALCdevice* device;
        ALCcontext* context;

    private:
        List<EventHandle> *events;
        SDL_Surface *screen;
        bool lock;
};






#endif
