#include "include/controls.h"
#include "include/sdl.h"
#include <math.h>

#define ANGLE 1
#define SPEED 2

bool right=false;
bool left=false;
bool up = false;
bool down = false;
bool move_right=false;
bool move_left=false;
bool move_foreward=false;
bool move_backward=false;

float move_direction_foreward=(float)SPEED/100;
float move_direction_left=0;

float position_x = 0;
float position_y = 0;
float position_z = -8.5;

void endprogramm(SDL_Event *event)
{
    exit(0);
}

void INIT_Controls(SDL* window)
{
    window->addEvent(SDL_QUIT,endprogramm);
    window->addEvent(SDL_KEYDOWN,haldeKeydown);
    window->addEvent(SDL_KEYUP,haldeKeyup);
    SDL_ShowCursor(SDL_DISABLE); //mausanzeige deaktivieren
    SDL_WM_GrabInput( SDL_GRAB_ON );// Maus einfangen
    window->addEvent(SDL_MOUSEMOTION,haldeMouse);
}

void haldeKeydown(SDL_Event *e)
{
    switch(e->key.keysym.sym)
    {
        case SDLK_ESCAPE:   // Exit programm if Escape is pressed.
            exit(0);
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
/*
    if(e->motion.yrel>0)
    {
        up = true;
    }
    else
    {
        down = true;
    }
*/
}

void move_camera(GLfloat move_x, GLfloat move_y, GLfloat move_z)
{
    position_x += move_x;
    position_y += move_y;
    position_z += move_z;

    glTranslatef(move_x, move_y, move_z);
}

void rotate_correctly(GLfloat angle, GLfloat rotate_x, GLfloat rotate_y, GLfloat rotate_z)
{
    glTranslatef(-position_x, -position_y, -position_z);
    glRotatef(angle, rotate_x, rotate_y, rotate_z);
    glTranslatef(position_x, position_y, position_z);
}

void rotation_handler(){    // Rotates the object if a key is pressed.
    if(right)
    {
        rotate_correctly(ANGLE,0,1,0);

        if(move_direction_foreward <= 0)
            move_direction_left += (float)1/((9000/SPEED)*(1/ANGLE));
        else
            move_direction_left -=  (float)1/((9000/SPEED)*(1/ANGLE));

        if(move_direction_left <= 0)
            move_direction_foreward -= (float)1/((9000/SPEED)*(1/ANGLE));
        else
            move_direction_foreward += (float)1/((9000/SPEED)*(1/ANGLE));

        right = false;

    }

    if(left)
    {
        rotate_correctly(-ANGLE,0,1,0);

        if(move_direction_foreward >= 0)
            move_direction_left += (float)1/((9000/SPEED)*(1/ANGLE));
        else
            move_direction_left -=  (float)1/((9000/SPEED)*(1/ANGLE));

        if(move_direction_left >= 0)
            move_direction_foreward -= (float)1/((9000/SPEED)*(1/ANGLE));
        else
            move_direction_foreward += (float)1/((9000/SPEED)*(1/ANGLE));

        left = false;
    }

}

void move_handler(){        // Moves the object if a key is pressed
    if(move_right)
        move_camera(-move_direction_foreward,0,move_direction_left);
    if(move_left)
        move_camera(move_direction_foreward,0,-move_direction_left);
    if(move_foreward)
        move_camera(move_direction_left,0,move_direction_foreward);
    if(move_backward)
        move_camera(-move_direction_left,0,-move_direction_foreward);
}
