#include <SDL_image.h>

#include <material.h>
#include <List.h>


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
}

bool Material::loadTexture2D(const char* file)
{
    GLint nOfColors = 0;
    GLenum texture_format = 0;
    this->BMPtexture = IMG_Load(file);

    if(this->BMPtexture == 0)
    {
        printf("textur %s not found\n",file);
        return false;
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

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &this->textureGL );
    glActiveTextureARB(this->textureGL);




    glBindTexture( GL_TEXTURE_2D, this->textureGL );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, this->BMPtexture->w, this->BMPtexture->h, 0,texture_format, GL_UNSIGNED_BYTE, this->BMPtexture->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );










    printf("texur %d %s loaded\n",this->textureGL,file);
    return true;
}

bool Material::loadBumpMap(const char* file)
{
    GLint nOfColors = 0;
    GLenum texture_format = 0;
    this->BMPbumpMap = IMG_Load(file);

    if(this->BMPbumpMap == 0)
    {
        printf("bumpmap %s not found\n",file);
        return false;
    }


    nOfColors = this->BMPbumpMap->format->BytesPerPixel;

    if (nOfColors == 4)
    {
        if (this->BMPbumpMap->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }

    else if (nOfColors == 3)
    {
        if (this->BMPbumpMap->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        printf("warning: %s is not truecolor.. this will probably break\n",file);
    }
    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &this->bumpmapGL );
    glActiveTextureARB(this->bumpmapGL);

    glBindTexture( GL_TEXTURE_2D, this->bumpmapGL );
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, this->BMPbumpMap->w, this->BMPbumpMap->h, 0,texture_format, GL_UNSIGNED_BYTE, this->BMPbumpMap->pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    printf("bumpmap %d %s loaded\n",this->bumpmapGL,file);
    return true;
}











