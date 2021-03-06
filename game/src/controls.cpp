#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include <sdl.h>
#include <controls.h>
#include <general_def.h>
#include <object.h>
#include <vector.h>
#include <scene.h>
#include <sound.h>
#include <physics/PhysicsEngine.h>

#define ROTATION_SPEED 0.5
#define MOVEMENT_SPEED 10

#define ROTATION_WIDTH (ROTATION_SPEED/mainScene->fps->get())
#define MOVEMENT_WIDTH (MOVEMENT_SPEED/mainScene->fps->get())


extern bool printFPS;
extern bool render;
extern Scene *mainScene;
extern Object *iccube;
extern FPS *fps;
Sound *shotSound;

Controls::Controls(SDL* window, EngineSettings *settings) : EventHandle()
{
    already_initialized = true;
    types.KeyDown = true;
    types.KeyUp = true;
    types.MouseMotion = true;
    types.Quit = true;
    window->addHandle(dynamic_cast<EventHandle *>(this));
    right_rotation = 0;
    down_rotation = 0;
    move_right = false;
    move_left = false;
    move_foreward = false;
    move_backward = false;
    move_up = false;
    move_down = false;
    fire = false;
    ghost_mode = false;

    SoundCache *SC = new SoundCache();
    shotSound = new Sound(SOUND(shot.wav),SC);
    shotSound->loadSound(SOUND(shot.wav));
    shotSound->settings->loop = true;
    shotSound->refreshProperties();
    shotSound->play();
    iccube->sounds->PushFront(shotSound);
    options = settings;
}

void Controls::handleQuit()
{
    render = false;
}

void Controls::screenshot(const char* filename, float width, float height)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0,width,height,24,0x000000FF, 0x0000FF00, 0x00FF0000,0);

    glReadBuffer(GL_FRONT);
    glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,(void*)surface->pixels);

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
            printFPS = toggle(printFPS);
            break;
        case SDLK_g:
            ghost_mode = toggle(ghost_mode);
            break;
        case SDLK_h:
            options->hud = toggle(options->hud);
            break;
        case SDLK_e:
            move_cube();
            break;
        case SDLK_p:
            screenshot("screenshot.bmp", options->width, options->height);
            break;
        case SDLK_r:
            shotSound->toggleLoop();
            break;
        case SDLK_LCTRL:
            fire = true;
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


void Controls::controls_handler(Camera *cam, Net *server)
{
    rotation_handler(cam);
    move_handler(cam);
    shoot_handler(cam, server);
}


void Controls::rotation_handler(Camera *cam){    // Rotates the camera if a key is pressed.

    cam->rotateY(ROTATION_WIDTH*right_rotation);

    vector lookDirectSave = vector(&cam->lookingDirection);

    vector temp = vector(cam->lookingDirection.x[0], 0, cam->lookingDirection.x[2]);
    temp.unify();

    cam->rotateX(-ROTATION_WIDTH*temp.x[2]*down_rotation);
    cam->rotateZ(-ROTATION_WIDTH*temp.x[0]*down_rotation);

    if((lookDirectSave.x[0] > 0) != (cam->lookingDirection.x[0] > 0))
        cam->lookingDirection = lookDirectSave;

    down_rotation = 0;
    right_rotation = 0;
}

void Controls::move_handler(Camera *cam){        // Moves the camera if a key is pressed
    cam->relativeToObject = iccube;

    vector moveDirection;

    if(move_right)
    {
        moveDirection =  vector(-cam->lookingDirection.x[2], 0, cam->lookingDirection.x[0]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        //cam->localPosition += moveDirection;
        iccube->localPosition += moveDirection;
    }

    if(move_left)
    {
        moveDirection =  vector(cam->lookingDirection.x[2], 0, -cam->lookingDirection.x[0]);
        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        //cam->localPosition += moveDirection;
        iccube->localPosition += moveDirection;
    }

    if(move_foreward)
    {
        if(ghost_mode)
            moveDirection =  vector(cam->lookingDirection.x[0], cam->lookingDirection.x[1], cam->lookingDirection.x[2]);
        else
            moveDirection =  vector(cam->lookingDirection.x[0], 0, cam->lookingDirection.x[2]);

        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        //cam->localPosition += moveDirection;
        iccube->localPosition += moveDirection;
    }

    if(move_backward)
    {
        if(ghost_mode)
            moveDirection =  vector(-cam->lookingDirection.x[0], -cam->lookingDirection.x[1], -cam->lookingDirection.x[2]);
        else
            moveDirection =  vector(-cam->lookingDirection.x[0], 0, -cam->lookingDirection.x[2]);

        moveDirection.unify();
        moveDirection *= MOVEMENT_WIDTH;

        //cam->localPosition += moveDirection;
        iccube->localPosition += moveDirection;
    }

    if(move_up)
    {
        if(!ghost_mode)
        {
            //cam->localPosition += vector(0.0, MOVEMENT_WIDTH, 0.0);
            iccube->localPosition += vector(0.0, MOVEMENT_WIDTH, 0.0);
        }
    }

    if(move_down)
    {
        if(!ghost_mode)
        {
            //cam->localPosition += vector(0.0, -MOVEMENT_WIDTH, 0.0);
            iccube->localPosition += vector(0.0, -MOVEMENT_WIDTH, 0.0);
        }
    }

}


void Controls::shoot_handler(Camera *cam, Net *server)
{
    Object *newObject = NULL;
    vector *newForce = NULL;
    BoundSphere *newSphere = NULL;

    if(fire)
    {
        fire = false;
        newObject = new Object(OBJECT(projectile.obj), "projectile", cam->getPosition() + (cam->lookingDirection * 3));
        newObject->physObj->setImpulse(cam->lookingDirection * 20);

        if(newObject->objType->boundSpheres->IsEmpty())
        {
            newSphere = new BoundSphere;
            newSphere->center = vector(0.0, 0.0, 0.0);
            newSphere->radian = 0.5;
            newObject->objType->boundSpheres->PushFront(newSphere);
        }

        server->addObject(newObject);

        mainScene->addObject(newObject);
    }
}


void Controls::move_cube()
{
    vector *testForce = new vector(3.0, 0, 0);
    iccube->physObj->addForce(testForce);
}


bool Controls::toggle(bool parameter)
{
    return parameter ? false : true;
}
