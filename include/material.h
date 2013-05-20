#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "types.h"



class Material
{
    public:
        Material(const char* textureFile);
        Material();
        ~Material();

        bool loadTexture2D(const char* file);
        bool loadBumpMap(const char* file);
        bool loadLightMap(const char* file);
        bool loadCliping(const char* file);

        SDL_Surface* BMPtexture;
        SDL_Surface* BMPbumpMap;
        SDL_Surface* BMPlightMap;
        GLuint textureGL;
        GLuint bumpmapGL;


};

#endif
