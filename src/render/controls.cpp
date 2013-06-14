#include <GL/gl.h>
#include <GL/glu.h>

#include <sdl.h>
#include <controls.h>
#include <general_def.h>
#include <object.h>
#include <vector.h>
#include <scene.h>
#define ANGLE 2
#define SPEED 5

bool right=false;
bool left=false;
bool up = false;
bool down = false;
bool move_right=false;
bool move_left=false;
bool move_foreward=false;
bool move_backward=false;

double move_direction_foreward=(double)SPEED/100;
double move_direction_left=0;

const double move_direction_change=(double)ANGLE/(9000/SPEED);

float position_x = STARTING_X;
float position_y = STARTING_Y;
float position_z = STARTING_Z;

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
            move_direction_left += move_direction_change;
        else
            move_direction_left -=  move_direction_change;

        if(move_direction_left <= 0)
            move_direction_foreward -= move_direction_change;
        else
            move_direction_foreward += move_direction_change;

        right = false;

    }

    if(left)
    {
        rotate_correctly(-ANGLE,0,1,0);

        if(move_direction_foreward >= 0)
            move_direction_left += move_direction_change;
        else
            move_direction_left -=  move_direction_change;

        if(move_direction_left >= 0)
            move_direction_foreward -= move_direction_change;
        else
            move_direction_foreward += move_direction_change;

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
        iccube->moveObject(0.002,direction, 10);
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
