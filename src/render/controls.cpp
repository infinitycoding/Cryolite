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
#include <sound.h>
#include <PhysicsEngine.h>

#define ROTATION_SPEED 0.5
#define MOVEMENT_SPEED 10

#define ROTATION_WIDTH (ROTATION_SPEED/mainScene->averageFPS)
#define MOVEMENT_WIDTH (MOVEMENT_SPEED/mainScene->averageFPS)


float Controls::right_rotation;
float Controls::down_rotation;

bool Controls::move_right;
bool Controls::move_left;
bool Controls::move_foreward;
bool Controls::move_backward;
bool Controls::move_up;
bool Controls::move_down;

bool Controls::ghost_mode;

bool Controls::already_initialized;


extern bool printFPS;
extern bool render;
extern Settings *gameSettings;
extern Scene *mainScene;
extern Object *iccube;
Sound *shotSound;

Controls::Controls(SDL* window) : EventHandle()
{
    if(!already_initialized)
    {
        already_initialized = true;
        types.KeyDown = true;
        types.KeyUp = true;
        types.MouseMotion = true;
        types.Quit = true;
        window->addHandle(object);
    }
    SoundCache *SC = new SoundCache();
    shotSound = new Sound(SOUND(shot.wav),SC);
    shotSound->loadSound(SOUND(shot.wav));
    shotSound->settings->loop = true;
    shotSound->refreshProperties();
    shotSound->play();
    iccube->sounds->PushFront(shotSound);
}

void Controls::handleQuit()
{
    render = false;
}

void Controls::screenshot(const char* filename)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0,gameSettings->width,gameSettings->height,24,0x000000FF, 0x0000FF00, 0x00FF0000,0);

    glReadBuffer(GL_FRONT);
    glReadPixels(0,0,gameSettings->width,gameSettings->height,GL_RGB,GL_UNSIGNED_BYTE,(void*)surface->pixels);

    SDL_SaveBMP(surface,filename);

    cout << "screenshot saved as " << filename << "." << endl;

    SDL_FreeSurface(surface);

}

void Controls::handleKeyDown(SDL_KeyboardEvent *e)
{
    switch(e->keysym.sym)
    {
        case SDLK_ESCAPE:   // Exit programm if Escape is pressed.
            handleQuit();
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
        case SDLK_f:
            toggle_printFPS();
            break;
        case SDLK_e:
            move_cube();
            break;
        case SDLK_p:
            Controls::screenshot("screenshot.bmp");
            break;
        case SDLK_r:
            shotSound->toggleLoop();
            break;
        default:
            break;

    }
}


void Controls::handleKeyUp(SDL_KeyboardEvent *e)
{
    switch(e->keysym.sym)
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

void Controls::handleMouseMotion(SDL_MouseMotionEvent *e)
{
    right_rotation = e->xrel;
    down_rotation = e->yrel;
}


void Controls::toggle_ghost()
{
    if(ghost_mode)
        ghost_mode = false;
    else
        ghost_mode = true;
}

void Controls::controls_handler(Camera *cam)
{
    rotation_handler(cam);
    move_handler(cam);
}


void Controls::rotation_handler(Camera *cam){    // Rotates the camera if a key is pressed.

    cam->rotateY(ROTATION_WIDTH*right_rotation);

    vector lookDirectSave = vector(&cam->lookingDirection);

    vector temp = vector(cam->lookingDirection.x, 0, cam->lookingDirection.z);
    temp.unify();

    cam->rotateX(-ROTATION_WIDTH*temp.z*down_rotation);
    cam->rotateZ(-ROTATION_WIDTH*temp.x*down_rotation);

    if((lookDirectSave.x > 0 ? true : false) !=(cam->lookingDirection.x > 0 ? true : false))
        cam->lookingDirection = lookDirectSave;

    down_rotation = 0;
    right_rotation = 0;
}

void Controls::move_handler(Camera *cam){        // Moves the camera if a key is pressed
    vector moveDirection;

    if(move_right)
    {
        moveDirection =  vector(-cam->lookingDirection.z, 0, cam->lookingDirection.x);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

    if(move_left)
    {
        moveDirection =  vector(cam->lookingDirection.z, 0, -cam->lookingDirection.x);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

    if(move_foreward)
    {
        if(ghost_mode)
            moveDirection =  vector(cam->lookingDirection.x, cam->lookingDirection.y, cam->lookingDirection.z);
        else
            moveDirection =  vector(cam->lookingDirection.x, 0, cam->lookingDirection.z);

        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

    if(move_backward)
    {
        if(ghost_mode)
            moveDirection =  vector(-cam->lookingDirection.x, -cam->lookingDirection.y, -cam->lookingDirection.z);
        else
            moveDirection =  vector(-cam->lookingDirection.x, 0, -cam->lookingDirection.z);

        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

    if(move_up)
    {
        moveDirection =  vector(0 , 1, 0);
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

    if(move_down)
    {
        moveDirection =  vector(0 , -1, 0);
        moveDirection *= MOVEMENT_WIDTH;

        cam->localPosition += moveDirection;
    }

}

void Controls::toggle_printFPS()
{
        if(printFPS)
            printFPS = false;
        else
            printFPS = true;

    return;
}

void Controls::move_cube()
{
    vector *testForce = new vector(0, 0, 3.0);
    iccube->physObj.forces->PushFront(testForce);
}
