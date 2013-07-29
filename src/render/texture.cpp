#include <texture.h>
#include <sdl.h>

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

    nr = SDL::loadTexture(filename);
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
    delete cachedTextures;
}


Texture *TextureCache::requestTexture(const char *filename)
{
    Texture *requestedTexture = searchTexture(filename);

    if(requestedTexture == NULL)
    {
        requestedTexture = new Texture(filename);
        cachedTextures->ListPushFront(requestedTexture);
    }

    return requestedTexture;
}


Texture *TextureCache::searchTexture(const char *filename)
{
    Texture *result = NULL;

    cachedTextures->ListSetFirst();

    while(!(cachedTextures->ListIsLast()))
    {
        result = cachedTextures->ListGetCurrent();

        if(!strncmp(result->file, filename, MAX_IMAGE_FILENAME_LENGTH))
            break;
        else
            result = NULL;

        cachedTextures->ListNext();
    }

    return result;
}


Texture *TextureCache::searchTexture(GLuint texnr)
{
    Texture *result = NULL;

    cachedTextures->ListSetFirst();

    while(!(cachedTextures->ListIsLast()))
    {
        result = cachedTextures->ListGetCurrent();

        if(result->nr == texnr)
            break;
        else
            result = NULL;

        cachedTextures->ListNext();
    }

    return result;
}


bool TextureCache::unloadTexture(const char *filename)
{
    Texture *texToDelete = searchTexture(filename);

    if(texToDelete != NULL)
        delete texToDelete;
    else
        return false;

    return true;
}


bool TextureCache::unloadTexture(GLuint texnr)
{
    Texture *texToDelete = searchTexture(texnr);

    if(texToDelete != NULL)
        delete texToDelete;
    else
        return false;

    return true;
}

