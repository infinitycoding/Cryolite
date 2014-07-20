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

#include <texture.h>
#include <mediaLayer.h>

using namespace std;



Texture::Texture()
{
    initTexture();
}


Texture::Texture(Texture *templateTexture)
{
    initTexture();

    nr = templateTexture->nr;
    strncpy(file, templateTexture->file, MAX_IMAGE_FILENAME_LENGTH);
}


Texture::Texture(const char *filename)
{
    initTexture();

    strncpy(file, filename, MAX_IMAGE_FILENAME_LENGTH);

    nr = MediaLayer::loadTexture(filename);
}


Texture::~Texture()
{
    glDeleteTextures(1, &nr);
}


void Texture::initTexture()
{
    nr = 0;
    memset(file, '\0', sizeof(file));
}



TextureCache::TextureCache()
{
    cachedTextures = new List<Texture>();
}


TextureCache::~TextureCache()
{

}


Texture *TextureCache::requestTexture(const char *filename)
{
    Texture *requestedTexture = searchTexture(filename);

    if(requestedTexture == NULL)
    {
        requestedTexture = new Texture(filename);
        cachedTextures->PushFront(requestedTexture);
    }

    return requestedTexture;
}


Texture *TextureCache::searchTexture(const char *filename)
{
    Texture *result = NULL;

    ListIterator<Texture> T = ListIterator<Texture>(cachedTextures);
    T.SetFirst();

    while(!(T.IsLast()))
    {
        result = T.GetCurrent();

        if(!strncmp(result->file, filename, MAX_IMAGE_FILENAME_LENGTH))
            break;
        else
            result = NULL;

        T.Next();
    }

    return result;
}


Texture *TextureCache::searchTexture(GLuint texnr)
{
    Texture *result = NULL;

    ListIterator<Texture> T = ListIterator<Texture>(cachedTextures);
    T.SetFirst();

    while(!(T.IsLast()))
    {
        result = T.GetCurrent();

        if(result->nr == texnr)
            break;
        else
            result = NULL;

        T.Next();
    }

    return result;
}


bool TextureCache::unloadTexture(const char *filename)
{
    Texture *texToDelete = NULL;

    ListIterator<Texture> T = ListIterator<Texture>(cachedTextures);
    T.SetFirst();

    while(!(T.IsLast()))
    {
        texToDelete = T.GetCurrent();

        if(!strncmp(texToDelete->file, filename, MAX_IMAGE_FILENAME_LENGTH))
        {
            T.Remove();
            return true;
        }

        T.Next();
    }

    return false;
}


bool TextureCache::unloadTexture(GLuint texnr)
{
    Texture *texToDelete = NULL;

    ListIterator<Texture> T = ListIterator<Texture>(cachedTextures);
    T.SetFirst();

    while(!(T.IsLast()))
    {
        texToDelete = T.GetCurrent();

        if(texToDelete->nr == texnr)
        {
            T.Remove();
            return true;
        }

        T.Next();
    }

    return false;
}

