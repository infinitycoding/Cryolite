#include <stdint.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

struct eventlist{
    struct eventlist *next;
    struct eventlist *prev;
    uint8_t event;
    void (*handle)(SDL_Event *event);
};

struct button{
    struct button *next;
    struct button *prev;
    void (*handle)(int MouseButton);
    int posx;
    int posy;
    int width;
    int height;
    SDL_Surface *image;
};

class SDL_GUI
{
    public:
        SDL_GUI(int width, int height, int bpp, int flags , uint32_t bgcolor, char *caption);
        ~SDL_GUI();
        void addEvent(uint8_t event, void (*handle)(SDL_Event *event));
        int remEvent(uint8_t event, void (*handle)(SDL_Event *event));
        void pollEvents();
        void render();
        int addButton(int width, int height, int posx, int posy, void (*handle)(int MouseButton),char *image);

    private:
        SDL_Surface *window;
        SDL_Surface *BaseBuffer;
        struct button *buttons;
        struct eventlist *events;
        void handleClick(SDL_Event *event);

};

