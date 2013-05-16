#include "include/modelview.h"

bool right=false;
bool left=false;
bool up=false;
bool down=false;
bool move_right=false;
bool move_left=false;
bool move_up=false;
bool move_down=false;
bool move_foreward=false;
bool move_backward=false;


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

void rotation_handler(){    // Rotates the object if a key is pressed.
    if(down)
        glRotatef(0.1,1,0,0);
    if(up)
        glRotatef(-0.1,1,0,0);
    if(right)
        glRotatef(0.1,0,1,0);
    if(left)
        glRotatef(-0.1,0,1,0);
}

void move_handler(){
    if(move_up)
        glTranslatef(0, -0.01, 0);
    if(move_down)
        glTranslatef(0, 0.01, 0);
    if(move_right)
        glTranslatef(-0.01,0,0);
    if(move_left)
        glTranslatef(0.01,0,0);
    if(move_foreward)
        glTranslatef(0,0,-0.01);
    if(move_backward)
        glTranslatef(0,0,0.01);
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
        case SDLK_w:
            move_up=true;
            break;
        case SDLK_s:
            move_down=true;
            break;
        case SDLK_a:
            move_left=true;
            break;
        case SDLK_d:
            move_right=true;
            break;
        case SDLK_1:
            move_foreward=true;
            break;
        case SDLK_2:
            move_backward=true;
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
        case SDLK_w:
            move_up=false;
            break;
        case SDLK_s:
            move_down=false;
            break;
        case SDLK_a:
            move_left=false;
            break;
        case SDLK_d:
            move_right=false;
            break;
        case SDLK_1:
            move_foreward=false;
            break;
        case SDLK_2:
            move_backward=false;
            break;
        default:
            break;
    }

}
