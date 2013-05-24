#include "sdl.h"


SDL::SDL(int width, int height, int flags, const char* caption)
{
    const SDL_VideoInfo *info = NULL;
    this->screen = NULL;
    this->lock = false;
    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        exit(-1);
    }

    atexit(SDL_Quit); // Quit SDL if the programm ends.

    info = SDL_GetVideoInfo();

    if( !info )
    {
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        exit(-1);
    }

    SDL_WM_SetCaption( caption, NULL );

    int bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


    this->screen = SDL_SetVideoMode( width, height, bpp, flags);
    if( this->screen == NULL ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(-1);
    }
    this->events = ListCreate();
}

SDL::~SDL()
{
    printf("Free Window buffer\n");
    //todo: free event list+structs
    SDL_FreeSurface(this->screen);
    printf("shutting down Application...\n");
    exit(0);
}

void SDL::addEvent(uint8_t event, void (*handle)(SDL_Event *event))
{
    struct eventHandler *newHandler = (struct eventHandler*) malloc(sizeof(struct eventHandler));
    newHandler->event = event;
    newHandler->handle = handle;
    while(this->lock){}
    this->lock = true;
        ListPushFront(this->events,newHandler);
    this->lock = false;
}

int SDL::removeEvent(uint8_t event, void (*handle)(SDL_Event *event))
{
    while(this->lock){}
    this->lock = true;
        ListSetFirst(this->events);
        while(!ListIsLast(this->events))
        {
            struct eventHandler* currentHandler = (struct eventHandler*) ListGetCurrent(this->events);
            if(currentHandler->event == event && currentHandler->handle == handle)
            {
                ListRemove(this->events);
            }
            else
            {
                ListNext(this->events);
            }

        }
    this->lock = false;
    return 0;
}

void SDL::pollEvents()
{
        SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        if(events)
        {
            ListSetFirst(this->events);
            while(!ListIsLast(this->events))
            {
                struct eventHandler* currentEvent = (struct eventHandler*) ListGetCurrent(this->events);
                if(currentEvent->event == event.type)
                {
                    currentEvent->handle(&event);
                }
                ListNext(this->events);
            }

        }
    }
}


