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

