#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL.h>

#include <sdl.h>
#include <camera.h>
#include <settings.h>
#include <Net.h>



class Controls : EventHandle
{
    public:
        Controls(SDL* window, EngineSettings *settings);

        void controls_handler(Camera *cam, Net *server);

        virtual void handleQuit();
        virtual void handleKeyDown(SDL_KeyboardEvent *e);
        virtual void handleKeyUp(SDL_KeyboardEvent *e);
        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);
        virtual void screenshot(const char* filename, float width, float height);

        virtual void move_cube();

        virtual bool toggle(bool parameter);

    private:
        void rotation_handler(Camera *cam);
        void move_handler(Camera *cam);
        void shoot_handler(Camera *cam, Net *server);


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

        bool already_initialized;

        EngineSettings *options;
};



#endif

