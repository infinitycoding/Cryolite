#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "sdl.h"
void INIT_Controls(SDL* window);
void rotation_handler();
void move_handler();

void haldeKeydown(SDL_Event *e);
void haldeKeyup(SDL_Event *e);
void haldeMouse(SDL_Event *e);
void toggle_printFPS(SDL_Event *e);
void moveCube(SDL_Event *e);


#endif
