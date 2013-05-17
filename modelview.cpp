#include "include/modelview.h"

bool right=false;
bool left=false;
bool move_right=false;
bool move_left=false;
bool move_foreward=false;
bool move_backward=false;

float move_direction_foreward=0.01;
float move_direction_left=0;

float position_x = 0;
float position_y = 0;
float position_z = -3.5;


void rotate_correctly(GLfloat angle, GLfloat rotate_x, GLfloat rotate_y, GLfloat rotate_z)
{
    glTranslatef(-position_x, -position_y, -position_z);
    glRotatef(angle, rotate_x, rotate_y, rotate_z);
    glTranslatef(position_x, position_y, position_z);
}

void move_camera(GLfloat move_x, GLfloat move_y, GLfloat move_z)
{
    position_x += move_x;
    position_y += move_y;
    position_z += move_z;

    glTranslatef(move_x, move_y, move_z);
}

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
    if(right)
    {
        rotate_correctly(0.1,0,1,0);

        if(move_direction_foreward <= 0)
            move_direction_left += (float)1/90000;
        else
            move_direction_left -=  (float)1/90000;

        if(move_direction_left <= 0)
            move_direction_foreward -= (float)1/90000;
        else
            move_direction_foreward += (float)1/90000;

    }

    if(left)
    {
        rotate_correctly(-0.1,0,1,0);

        if(move_direction_foreward >= 0)
            move_direction_left += (float)1/90000;
        else
            move_direction_left -=  (float)1/90000;

        if(move_direction_left >= 0)
            move_direction_foreward -= (float)1/90000;
        else
            move_direction_foreward += (float)1/90000;
    }
}

void move_handler(){        // Moves the object if a key is pressed
    if(move_right)
        move_camera(-move_direction_foreward,0,move_direction_left);
    if(move_left)
        move_camera(move_direction_foreward,0,-move_direction_left);
    if(move_foreward)
        move_camera(move_direction_left,0,move_direction_foreward);
    if(move_backward)
        move_camera(-move_direction_left,0,-move_direction_foreward);
}

void handle_key_down( SDL_keysym *keysym ){
    switch( keysym->sym ) {
        case SDLK_ESCAPE:   // Exit programm if Escape is pressed.
            exit(0);
            break;
        case SDLK_RIGHT:
            right=true;
            break;
        case SDLK_LEFT:
            left=true;
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
        default:
            break;
    }

}


void handle_key_up( SDL_keysym *keysym ){
    switch( keysym->sym ) {
        case SDLK_RIGHT:
            right=false;
            break;
        case SDLK_LEFT:
            left=false;
            break;
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
        default:
            break;
    }

}
