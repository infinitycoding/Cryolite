#include "include/modelview.h"

bool right=false;
bool left=false;
bool up=false;
bool down=false;
bool run = true;

void process_events( void ){
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
            case SDL_KEYDOWN:                           // Keydowns has a subfunction
                handle_key_down( &event.key.keysym );
                break;
            case SDL_KEYUP:                             // Keyups has a subfunction
                handle_key_up( &event.key.keysym );
                break;
            case SDL_QUIT:                              // Exit the programm if the X is pressed.
                exit(0);
                break;
            default:
                break;
        }

    }

}

void rotation_handler(){
    if(down)
        glRotatef(0.1,1,0,0);
    if(up)
        glRotatef(-0.1,1,0,0);
    if(right)
        glRotatef(0.1,0,1,0);
    if(left)
        glRotatef(-0.1,0,1,0);
}

void handle_key_down( SDL_keysym *keysym ){
    switch( keysym->sym ) {
        case SDLK_ESCAPE:   // Exit programm if Escape is pressed.
            exit(0);
            break;
        case SDLK_DOWN:     // Activate the rotation on keypress.
            down=true;
            break;
        case SDLK_UP:
            up=true;
            break;
        case SDLK_RIGHT:
            right=true;
            break;
        case SDLK_LEFT:
            left=true;
            break;
        default:
            break;
    }

}


void handle_key_up( SDL_keysym *keysym ){
    switch( keysym->sym ) {
        case SDLK_DOWN:     // Stop the rotation on keyrelease.
            down=false;
            break;
        case SDLK_UP:
            up=false;
            break;
        case SDLK_RIGHT:
            right=false;
            break;
        case SDLK_LEFT:
            left=false;
            break;
        default:
            break;
    }

}
