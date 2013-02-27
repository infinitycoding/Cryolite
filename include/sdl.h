#ifndef CRYOLITE_SDL_H
#define CRYOLITE_SDL_H
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL_image.h>

SDL_Surface* init_SDL(int width, int height, int flags, const char* caption);
GLuint loadTexture2D(const char* file);


#endif
