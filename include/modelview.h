#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void process_events( );
void rotation_handler();
void handle_key_down( SDL_keysym *keysym );
void handle_key_up( SDL_keysym *keysym );


#endif
