#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL.h>
#include <sdl.h>
#include <camera.h>



class Controls : EventHandle
{
    public:
        Controls(SDL* window);

        void controls_handler(Camera *cam);

        virtual void handleQuit();
        virtual void handleKeyDown(SDL_KeyboardEvent *e);
        virtual void handleKeyUp(SDL_KeyboardEvent *e);
        virtual void handleMouseMotion(SDL_MouseMotionEvent *e);
        virtual void screenshot(const char* filename);

        virtual void toggle_printFPS();
        virtual void move_cube();

        virtual void toggle_ghost();

    private:
        void rotation_handler(Camera *cam);
        void move_handler(Camera *cam);


        static float right_rotation;
        static float down_rotation;

        static bool move_right;
        static bool move_left;
        static bool move_foreward;
        static bool move_backward;
        static bool move_up;
        static bool move_down;

        static bool ghost_mode;

        static bool already_initialized;
};



#endif

