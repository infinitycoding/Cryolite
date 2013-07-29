#include <sdl.h>
#include <SDL_mixer.h>
#include <settings.h>

extern Settings *gameSettings;


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
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, gameSettings->multisamples);


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

    this->events = new List<EventHandle>;
}

SDL::~SDL()
{
    printf("Free Window buffer\n");
    //todo: free event list+structs
    SDL_FreeSurface(this->screen);
    printf("shutting down Application...\n");
    exit(0);
}

void SDL::addHandle(EventHandle *Instance)
{
    while(this->lock){}
    this->lock = true;
        this->events->ListPushFront(Instance);
    this->lock = false;
}

int SDL::removeHandle(EventHandle *Instance)
{
    while(this->lock){}
    this->lock = true;
        this->events->ListSetFirst();
        while(!this->events->ListIsLast())
        {
            EventHandle* currentHandler = this->events->ListGetCurrent();
            if(currentHandler == Instance)
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
                EventHandle* currentEvent = (EventHandle*) this->events->ListGetCurrent();

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
                    /*case SDL_MOUSEWHEEL:
                        if(currentEvent->types.MouseWheel) currentEvent->handle->handleMouseWheel(event);
                        break;*/
                    case SDL_QUIT:
                        if(currentEvent->types.Quit) currentEvent->handleQuit();
                        break;
                };

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

EventHandle::EventHandle()
{
    object = this;
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
//virtual void handleMouseWheel(SDL_MouseWheelEvent *e);
void EventHandle::handleQuit(){};
EventHandle::~EventHandle(){}


