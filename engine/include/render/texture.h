#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <cstring>

#include <util/List.h>


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


class TextureCache
{
    public:
        TextureCache();
        ~TextureCache();

        Texture *requestTexture(const char *filename);

        Texture *searchTexture(const char *filename);
        Texture *searchTexture(GLuint texnr);

        bool unloadTexture(const char *filename);
        bool unloadTexture(GLuint texnr);


    protected:
        List<Texture> *cachedTextures;
};


#endif
