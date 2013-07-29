#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED



#include <SDL.h>
#include <SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <cstring>

#include <List.h>


#define MAX_IMAGE_FILENAME_LENGTH 30



class Texture
{
    public:
        Texture();
        Texture(Texture *templateTexture);
        Texture(const char *filename);
        ~Texture();

        void initTexture();

        static GLuint loadTexture(const char *filename);



        GLuint nr;
        char file[MAX_IMAGE_FILENAME_LENGTH];
};



#endif
