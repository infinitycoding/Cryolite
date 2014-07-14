#include <mediaLayer.h>

#include <SDL_image.h>
#include <iostream>

#ifdef _WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#define ON_WINDOWS true
#endif
#ifndef _WIN32
#define ON_WINDOWS false
#endif

using namespace std;

bool sdlInitiaed = false;
bool audioInitiaed = false;

/**
 * @brief Creates a new Window with independent Evenent and audio handling.
 * @param width Width of the new window.
 * @param height Height of the new window.
 * @param flags The flags for the SDL-Screen
 * @param caption The capton of the new window.
 * @param multisamples The optional Multisample level
 */
MediaLayer::MediaLayer(int width, int height, int flags, const char* caption, int multisamples = 0)
{
    this->screen = NULL;
    this->width = width;
    this->height = height;
    // initiate SDL
    if(!sdlInitiaed)
    {
        sdlInitiaed = true;
        if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
        {
            cerr<<"Video initialization failed: "<<SDL_GetError()<<endl;
            exit(-1);
        }

        atexit(MediaLayer::MediaExit); // Quit SDL if the programm ends.
    }
    // initiate SDL_Mixer
    if(!audioInitiaed)
    {
        audioInitiaed = true;
        if(Mix_OpenAudio(AUDIORATE, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
        {
            cerr<<"SDL Mixer initialization failed: "<<Mix_GetError()<<endl;
            exit(-1);
        }
    }


    screen = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderContext =  SDL_GL_CreateContext(screen);



    if(flags & SDL_WINDOW_OPENGL)
    {
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisamples);
    }


    if( this->screen == NULL ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(-1);
    }

    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    this->events = new List<EventHandle>;
}

/**
 * @brief Destroys a MediaLayer
 */
MediaLayer::~MediaLayer()
{

    alcDestroyContext(context);
    alcCloseDevice(device);
    delete events;
    SDL_DestroyWindow(this->screen);
}

/**
 * @brief Adds a EventHandle to the current MediaLayer.
 * @param Instance A pointer to a EventHandle Instance
 */
void MediaLayer::addHandle(EventHandle *Instance)
{
    this->events->PushFront(Instance);
}

/**
 * @brief Removes a EventHandle from the the current MediaLayer.
 * @param Instance A pointer to a EventHandle Instance
 */
int MediaLayer::removeHandle(EventHandle *Instance)
{
    ListIterator<EventHandle> E = ListIterator<EventHandle>(events);
    E.SetFirst();
    while(!E.IsLast())
    {
        EventHandle* currentHandler = E.GetCurrent();
        if(currentHandler == Instance)
        {
            E.Remove();
        }
        else
        {
            E.Next();
        }

    }
    return 0;
}

/**
 * @brief Handles all events occured since the last call and redirects them to ther handling instance.
 */
void MediaLayer::pollEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(events)
        {
            ListIterator<EventHandle> E = ListIterator<EventHandle>(events);
            E.SetFirst();
            while(!E.IsLast())
            {
                EventHandle* currentEvent = (EventHandle*) E.GetCurrent();
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        if(currentEvent->types.KeyDown) currentEvent->handleKeyDown(&event.key);
                        break;
                    case SDL_KEYUP:
                        if(currentEvent->types.KeyUp) currentEvent->handleKeyUp(&event.key);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(currentEvent->types.MouseButtonDown) currentEvent->handleMouseButtonDown(&event.button);
                        break;
                    case  SDL_MOUSEBUTTONUP:
                        if(currentEvent->types.MouseButtonUp) currentEvent->handleMouseButtonUp(&event.button);
                        break;
                    case SDL_MOUSEMOTION:
                        if(currentEvent->types.MouseMotion) currentEvent->handleMouseMotion(&event.motion);
                        break;
                    case SDL_MOUSEWHEEL:
                        if(currentEvent->types.MouseWheel) currentEvent->handleMouseWheel(&event.wheel);
                        break;
                    case SDL_QUIT:
                        if(currentEvent->types.Quit) currentEvent->handleQuit();
                        break;
                };

                E.Next();
            }

        }
    }
}

GLuint MediaLayer::loadTexture(const char *filename)
{
    return loadTexture(filename,GL_NEAREST,GL_NEAREST);
}

GLuint MediaLayer::loadTexture(const char *filename,GLenum MinFilter,GLenum MagFilter)
{
    GLint nOfColors = 0;
    GLenum texture_format = 0;
    SDL_Surface *SDL_Texture = IMG_Load(filename);
    GLuint GL_Texture = 0;

    if(SDL_Texture == NULL)
    {
        printf("textur %s not found\n",filename);
        return 0;
    }


    nOfColors = SDL_Texture->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (SDL_Texture->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (SDL_Texture->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        fprintf(stderr,"warning: %s is not truecolor.. this will probably break\n", filename);
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &GL_Texture );
    #ifndef _WIN32
    glActiveTexture(GL_Texture);
    #endif
    glBindTexture( GL_TEXTURE_2D, GL_Texture );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, SDL_Texture->w, SDL_Texture->h, 0,texture_format, GL_UNSIGNED_BYTE, SDL_Texture->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter );


    cout << "texur " << GL_Texture << " " << filename << " loaded" << endl;

    SDL_FreeSurface(SDL_Texture);
    return GL_Texture;
}

GLuint MediaLayer::surfToTexture(SDL_Surface *surf){return surfToTexture(surf,GL_NEAREST,GL_NEAREST);}

GLuint MediaLayer::surfToTexture(SDL_Surface *surf,GLenum MinFilter,GLenum MagFilter)
{

    GLint nOfColors = 0;
    GLenum texture_format = 0;
    GLuint GL_Texture = 0;

    if(surf == NULL)
    {
        cerr<<"texture pointer is NULL. Returned NULL texture"<<endl;
        return 0;
    }


    nOfColors = surf->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (surf->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (surf->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        cerr<<"warning: surface is not a truecolor surface .. this will probably break"<<endl;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &GL_Texture );
    #ifndef _WIN32
    glActiveTexture(GL_Texture);
    #endif
    glBindTexture( GL_TEXTURE_2D, GL_Texture );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surf->w, surf->h, 0,texture_format, GL_UNSIGNED_BYTE, surf->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter );

    return GL_Texture;
}

ALuint MediaLayer::chunkToBuffer(Mix_Chunk *sound)
{
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, sound->abuf, sound->alen, 44100);
    return buffer;
}


void MediaLayer::MediaExit()
{
    SDL_Quit();
    Mix_CloseAudio();
    printf("Application closed \n");
};

EventHandle::EventHandle()
{
    types.KeyUp = false;
    types.KeyDown = false;
    types.MouseButtonDown = false;
    types.MouseButtonUp = false;
    types.MouseMotion = false;
    types.MouseWheel = false;
    types.Quit = false;
}

void EventHandle::handleKeyDown(SDL_KeyboardEvent *e){}
void EventHandle::handleKeyUp(SDL_KeyboardEvent *e){}
void EventHandle::handleMouseButtonUp(SDL_MouseButtonEvent *e){}
void EventHandle::handleMouseButtonDown(SDL_MouseButtonEvent *e){}
void EventHandle::handleMouseMotion(SDL_MouseMotionEvent *e){}
void EventHandle::handleMouseWheel(SDL_MouseWheelEvent *e){};
void EventHandle::handleQuit(){};
EventHandle::~EventHandle(){}


