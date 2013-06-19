#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include <sdl.h>
#include <controls.h>
#include <general_def.h>
#include <object.h>
#include <vector.h>
#include <scene.h>
#define ROTATION_SPEED 0.05
#define SPEED 10

bool right=false;
bool left=false;
bool up = false;
bool down = false;
bool move_right=false;
bool move_left=false;
bool move_foreward=false;
bool move_backward=false;

extern bool printFPS;
extern bool render;
extern Scene *mainScene;

void endprogramm(SDL_Event *event)
{
    render = false;
}

void INIT_Controls(SDL* window)
{
    window->addEvent(SDL_QUIT,endprogramm);
    window->addEvent(SDL_KEYDOWN,haldeKeydown);
    window->addEvent(SDL_KEYUP,haldeKeyup);
    SDL_ShowCursor(SDL_DISABLE); //mausanzeige deaktivieren
    SDL_WM_GrabInput( SDL_GRAB_ON );// Maus einfangen
    window->addEvent(SDL_MOUSEMOTION,haldeMouse);
    window->addEvent(SDL_KEYDOWN,toggle_printFPS);
    window->addEvent(SDL_KEYDOWN,moveCube);
    window->addEvent(SDL_KEYDOWN,rotateCube);
}

void haldeKeydown(SDL_Event *e)
{
    switch(e->key.keysym.sym)
    {
        case SDLK_ESCAPE:   // Exit programm if Escape is pressed.
            endprogramm(e);
            break;
        case SDLK_w:
            move_foreward=true;
            break;
        case SDLK_s:
            move_backward=true;
            break;
        case SDLK_a:
            move_left=true;
            break;
        case SDLK_d:
            move_right=true;
            break;
        default:
            break;

    }

}


void haldeKeyup(SDL_Event *e)
{
    switch(e->key.keysym.sym)
    {
        case SDLK_w:
            move_foreward=false;
            break;
        case SDLK_s:
            move_backward=false;
            break;
        case SDLK_a:
            move_left=false;
            break;
        case SDLK_d:
            move_right=false;
            break;
        default:
            break;
    }
}

void haldeMouse(SDL_Event *e)
{
    if(e->motion.xrel>0)
    {
        right=true;
    }
    else
    {
        left=true;
    }

    if(e->motion.yrel>0)
    {
        up = true;
    }
    else
    {
        down = true;
    }

}


void rotation_handler(Camera *cam){    // Rotates the camera if a key is pressed.
    if(right)
    {
        cam->lookingDirection.elements[0] = cam->lookingDirection.elements[0] * cos(ROTATION_SPEED) - cam->lookingDirection.elements[2] * sin(ROTATION_SPEED);
        cam->lookingDirection.elements[2] = cam->lookingDirection.elements[0] * sin(ROTATION_SPEED) + cam->lookingDirection.elements[2] * cos(ROTATION_SPEED);

        right = false;
    }

    if(left)
    {
        cam->lookingDirection.elements[0] = cam->lookingDirection.elements[0] * cos(-ROTATION_SPEED) - cam->lookingDirection.elements[2] * sin(-ROTATION_SPEED);
        cam->lookingDirection.elements[2] = cam->lookingDirection.elements[0] * sin(-ROTATION_SPEED) + cam->lookingDirection.elements[2] * cos(-ROTATION_SPEED);

        left = false;
    }

    if(up)
    {
        up = false;
    }

    if(down)
    {
        down = false;
    }

}

void move_handler(Camera *cam){        // Moves the camera if a key is pressed
    if(move_right)
    {
        cam->position.elements[0] -= cam->lookingDirection.elements[2];
        cam->position.elements[2] += cam->lookingDirection.elements[0];
    }

    if(move_left)
    {
        cam->position.elements[0] += cam->lookingDirection.elements[2];
        cam->position.elements[2] -= cam->lookingDirection.elements[0];
    }

    if(move_foreward)
    {
        cam->position.elements[0] += cam->lookingDirection.elements[0];
        cam->position.elements[2] += cam->lookingDirection.elements[2];
    }

    if(move_backward)
    {
        cam->position.elements[0] -= cam->lookingDirection.elements[0];
        cam->position.elements[2] -= cam->lookingDirection.elements[2];
    }

}

void toggle_printFPS(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_f)
    {
        if(printFPS)
            printFPS = false;
        else
            printFPS = true;
    }

    return;
}
extern Object *iccube;

void moveCube(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_e)
    {
        vector direction = vector(0, 0, 1);
        iccube->moveObject(0.002,direction, 3);
    }

    return;
}

void rotateCube(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_r)
    {
        vector direction = vector(0, 0, 1);
        iccube->rotateObject(360,2,0.05,direction);
    }

    return;
}
