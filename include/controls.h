#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL.h>
#include <camera.h>


void INIT_Controls(SDL* window);
void rotation_handler(Camera *cam);
void move_handler(Camera *cam);

void haldeKeydown(SDL_Event *e);
void haldeKeyup(SDL_Event *e);
void haldeMouse(SDL_Event *e);
void toggle_printFPS(SDL_Event *e);
void moveCube(SDL_Event *e);
void rotateCube(SDL_Event *e);


#endif
