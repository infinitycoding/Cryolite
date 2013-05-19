#include "include/material.h"
#include "include/list.h"
#include <SDL_image.h>

Material::Material(const char* textureFile)
{
    this->BMPtexture = NULL;
    this->BMPbumpMap = NULL;
    this->BMPlightMap = NULL;
    this->textureGL = 0;
    this->loadTexture2D(textureFile);
}


Material::Material()
{
    this->BMPtexture = NULL;
    this->BMPbumpMap = NULL;
    this->BMPlightMap = NULL;
    this->textureGL = 0;
}

Material::~Material(){
    if(this->BMPtexture) SDL_FreeSurface(this->BMPtexture);
    if(this->BMPbumpMap) SDL_FreeSurface(this->BMPbumpMap);
    if(this->BMPlightMap) SDL_FreeSurface(this->BMPlightMap);

    //todo free cliping list

}

bool Material::loadTexture2D(const char* file)
{
    GLint nOfColors = 0;
    GLenum texture_format = 0;
    this->BMPtexture = IMG_Load(file);

    if(this->BMPtexture == 0)
    {
        printf("textur %s not found",file);
        return false;
    }
    if ( (this->BMPtexture->w & (this->BMPtexture->w - 1)) != 0 )
    {
        printf("warning: %s's width is not a power of 2\n",file);
    }
    if ( (this->BMPtexture->h & (this->BMPtexture->h - 1)) != 0 )
    {
        printf("warning: %s's height is not a power of 2\n",file);
    }

    nOfColors = this->BMPtexture->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (this->BMPtexture->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (this->BMPtexture->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        printf("warning: %s is not truecolor.. this will probably break\n",file);
    }

    glGenTextures( 1, &this->textureGL );
    glBindTexture( GL_TEXTURE_2D, this->textureGL );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, this->BMPtexture->w, this->BMPtexture->h, 0,texture_format, GL_UNSIGNED_BYTE, this->BMPtexture->pixels );
    printf("texur %d %s loaded\n",this->textureGL,file);
    return true;
}











