#include <sdl.h>
#include <SDL_mixer.h>


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

    atexit(SDL::SDLexit); // Quit SDL if the programm ends.

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

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        fprintf(stderr,"Faild to initiate SDL Mixer %s\n",Mix_GetError());
        exit(-1);
    }

    this->events = new List<struct eventHandler>;
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
    struct eventHandler *newHandler = new struct eventHandler;
    newHandler->event = event;
    newHandler->handle = handle;
    while(this->lock){}
    this->lock = true;
        this->events->ListPushFront(newHandler);
    this->lock = false;
}

int SDL::removeEvent(uint8_t event, void (*handle)(SDL_Event *event))
{
    while(this->lock){}
    this->lock = true;
        this->events->ListSetFirst();
        while(!this->events->ListIsLast())
        {
            struct eventHandler* currentHandler = (struct eventHandler*) this->events->ListGetCurrent();
            if(currentHandler->event == event && currentHandler->handle == handle)
            {
                this->events->ListRemove();
            }
            else
            {
                this->events->ListNext();
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
            this->events->ListSetFirst();
            while(!this->events->ListIsLast())
            {
                struct eventHandler* currentEvent = (struct eventHandler*) this->events->ListGetCurrent();
                if(currentEvent->event == event.type)
                {
                    currentEvent->handle(&event);
                }
                this->events->ListNext();
            }

        }
    }
}

void SDL::SDLexit()
{
    SDL_Quit();
    Mix_CloseAudio();
    printf("Application closed \n");
};


