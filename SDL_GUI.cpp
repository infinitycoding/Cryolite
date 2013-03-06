#include "include/sdl_gui.h"




SDL_GUI::SDL_GUI(int width, int height, int bpp, int flags , uint32_t bgcolor, char *caption)
{
    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        exit(-1);
    }

    atexit(SDL_Quit);

    SDL_WM_SetCaption( caption, NULL );

    window = SDL_SetVideoMode( width, height, bpp, flags);
    if(  window == NULL ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(-1);
    }
    events = NULL;
    buttons = NULL;

    SDL_Rect dstrect;
    dstrect.h = height;
    dstrect.w = width;
    dstrect.x = 0;
    dstrect.y = 0;
    BaseBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp, 0xff000000 , 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_FillRect(BaseBuffer, &dstrect, bgcolor );


}

SDL_GUI::~SDL_GUI()
{
    if(events)
    {
        struct eventlist *temp = events->next;
        while(temp->next != events)
        {
            free(temp->prev);
            temp = temp->next;
        }
        free(temp);
    }

    if(buttons)
    {
        struct button *temp = buttons->next;
        while(temp->next != buttons)
        {
            free(temp->prev);
            temp = temp->next;
        }
        free(temp);
    }
}

void SDL_GUI::addEvent(uint8_t event, void (*handle)(SDL_Event *event))
{
    if(events)
    {
        struct eventlist *newEvent = (struct eventlist *) malloc(sizeof(struct eventlist));
        newEvent->event = event;
        newEvent->handle = handle;
        newEvent->prev = events->prev;
        newEvent->next = events;
        events->prev->next = newEvent;
        events->prev = newEvent;
    }
    else
    {
        events = (struct eventlist *) malloc(sizeof(struct eventlist));
        events->prev = events;
        events->next = events;
        events->event = event;
        events->handle = handle;
    }

}

int SDL_GUI::remEvent(uint8_t event, void (*handle)(SDL_Event *event))
{
    bool found = false;
    if(events->handle == handle && events->event == event)
    {
        if(events->next == events)
        {
            free(events);
            events = NULL;
            return 0;
        }
        struct eventlist *destEvent = events;
        events = events->prev;
        events->next = destEvent->next;
        destEvent->next->prev = events;
        free(destEvent);
        found = true;
    }

    struct eventlist *temp = events->next;
    while(temp != events)
    {
        if(temp->handle == handle && temp->event == event)
        {
            if(temp->next == temp)
            {
                free(temp);
                events = NULL;
                return 0;
            }

            struct eventlist *destEvent = temp;
            temp = temp->prev;
            if(temp == events)
            {
                events = temp;
            }
            temp->next = destEvent->next;
            destEvent->next->prev = temp;
            free(destEvent);
            found = true;
        }
        temp = temp->next;
    }

    if(found)
    {
        return 0;
    }
    return -1; //event not found
}

void SDL_GUI::pollEvents()
{
        SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        if(events)
        {
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                this->handleClick(&event);
            }

            if(events->event == event.type)
            {
                events->handle(&event);
            }

            struct eventlist *temp = events->next;

            while(temp != events)
            {
                if(temp->event == event.type)
                {
                    temp->handle(&event);
                }
                temp = temp->next;
            }

        }
    }
}



void SDL_GUI::render()
{
    SDL_BlitSurface(BaseBuffer, NULL, window, NULL);
    //render other layers
    SDL_Flip( window );
}

int SDL_GUI::addButton(int width, int height, int posx, int posy, void (*handle)(int MouseButton),char *image)
{
    SDL_Surface* img = IMG_Load(image);
    if(img == 0)
    {
        return -1; //image not found
    }
    SDL_Rect srcrect;
    srcrect.h = height;
    srcrect.w = width;
    srcrect.x = 0;
    srcrect.y = 0;

    SDL_Rect destrect;
    destrect.x = posx;
    destrect.y = posy;

    SDL_BlitSurface(img, &srcrect, BaseBuffer, &destrect);

    if(buttons)
    {
        struct button *newButton = (struct button*) malloc(sizeof(struct button));
        newButton->posx = posx;
        newButton->posy = posy;
        newButton->width = width;
        newButton->height = height;
        newButton->handle = handle;
        newButton->image = img;

        newButton->prev = buttons->prev;
        newButton->next = buttons;
        buttons->prev->next = newButton;
        buttons->prev = newButton;
    }
    else
    {
        buttons = (struct button*) malloc(sizeof(struct button));
        buttons->posx = posx;
        buttons->posy = posy;
        buttons->width = width;
        buttons->height = height;
        buttons->handle = handle;
        buttons->image = img;

        buttons->next = buttons;
        buttons->prev = buttons;
    }
    return 0;
}

void SDL_GUI::handleClick(SDL_Event *event)
{
    int x = event->button.x;
    int y = event->button.y;
    if(buttons)
    {
        if(buttons->posx <= x && buttons->posy <= y && x <= buttons->posx+buttons->width && y <= buttons->posy+buttons->height)
        {
            buttons->handle(event->button.button);
        }
        struct button *temp = buttons->next;
        while(temp != buttons)
        {
            if(temp->posx <= x && temp->posy <= y && x <= temp->posx+temp->width && y <= temp->posy+temp->height)
            {
                temp->handle(event->button.button);
            }
            temp = temp->next;
        }
    }
}

