#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include <sdl.h>
#include <controls.h>
#include <general_def.h>
#include <object.h>
#include <vector.h>
#include <scene.h>
#include <settings.h>

#define ROTATION_SPEED 5
#define MOVEMENT_SPEED 10

#define ROTATION_WIDTH (ROTATION_SPEED/mainScene->averageFPS)
#define MOVEMENT_WIDTH (MOVEMENT_SPEED/mainScene->averageFPS)


bool Controls::right;
bool Controls::left;
bool Controls::up;
bool Controls::down;

bool Controls::move_right;
bool Controls::move_left;
bool Controls::move_foreward;
bool Controls::move_backward;
bool Controls::move_up;
bool Controls::move_down;

bool Controls::already_initialized;


extern bool printFPS;
extern bool render;
extern Settings *gameSettings;
extern Scene *mainScene;

Controls::Controls(SDL* window)
{
    if(!already_initialized)
    {
        already_initialized = true;
        window->addEvent(SDL_QUIT,endprogramm);
        window->addEvent(SDL_KEYDOWN,haldeKeydown);
        window->addEvent(SDL_KEYUP,haldeKeyup);
        window->addEvent(SDL_MOUSEMOTION,haldeMouse);
        window->addEvent(SDL_KEYDOWN,toggle_printFPS);
        window->addEvent(SDL_KEYDOWN,moveCube);
        window->addEvent(SDL_KEYDOWN,rotateCube);

        if(gameSettings->captureMouse)
        {
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WM_GrabInput( SDL_GRAB_ON );
        }
    }
}

void Controls::endprogramm(SDL_Event *event)
{
    render = false;
}

void Controls::haldeKeydown(SDL_Event *e)
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
        case SDLK_SPACE:
            move_up=true;
            break;
        case SDLK_LSHIFT:
            move_down=true;
            break;
        default:
            break;

    }
}


void Controls::haldeKeyup(SDL_Event *e)
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
        case SDLK_SPACE:
            move_up=false;
            break;
        case SDLK_LSHIFT:
            move_down=false;
            break;
        default:
            break;
    }
}

void Controls::haldeMouse(SDL_Event *e)
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


void Controls::controls_handler(Camera *cam)
{
    rotation_handler(cam);
    move_handler(cam);
}


void Controls::rotation_handler(Camera *cam){    // Rotates the camera if a key is pressed.
    if(right)
    {
        cam->rotateY(ROTATION_WIDTH);

        right = false;
    }

    if(left)
    {
        cam->rotateY(-ROTATION_WIDTH);

        left = false;
    }

    /*if(up)
    {
        cam->rotateX(-ROTATION_WIDTH);

        up = false;
    }

    if(down)
    {
        cam->rotateX(ROTATION_WIDTH);

        down = false;
    }*/

}

void Controls::move_handler(Camera *cam){        // Moves the camera if a key is pressed
    vector moveDirection;

    if(move_right)
    {
        moveDirection =  vector(-cam->lookingDirection.elements[2], 0, cam->lookingDirection.elements[0]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

    if(move_left)
    {
        moveDirection =  vector(cam->lookingDirection.elements[2], 0, -cam->lookingDirection.elements[0]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

    if(move_foreward)
    {
        moveDirection =  vector(cam->lookingDirection.elements[0], 0, cam->lookingDirection.elements[2]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

    if(move_backward)
    {
        moveDirection =  vector(-cam->lookingDirection.elements[0], 0, -cam->lookingDirection.elements[2]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

    if(move_up)
    {
        moveDirection =  vector(0 , 1, 0);
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

    if(move_down)
    {
        moveDirection =  vector(0 , -1, 0);
        moveDirection *= MOVEMENT_WIDTH;

        cam->position += moveDirection;
    }

}

void Controls::toggle_printFPS(SDL_Event *e)
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

void Controls::moveCube(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_e)
    {
        vector direction = vector(0, 0, 1);
        iccube->moveObject(0.002,direction, 3);
    }

    return;
}

void Controls::rotateCube(SDL_Event *e)
{
    if(e->key.keysym.sym == SDLK_r)
    {
        vector direction = vector(0, 0, 1);
        iccube->rotateObject(360,2,0.05,direction);
    }

    return;
}
