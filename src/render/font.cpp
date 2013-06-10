#include <font.h>

Font::Font()
{
    if (TTF_Init() == -1)
    {
        printf("Could not initialize SDL_ttf: %s \n", TTF_GetError());
        exit(-1);
    }
}

Font::Font(char *font)
{

}

Font:: ~Font()
{

}

bool Font::LoadFont(char *font,char* name, int ptsize)
{
    TTF_Font* font_ptr;
    font_ptr = TTF_OpenFont(font, ptsize);
    if (font_ptr == NULL){
      printf("Could not load font: %s %s \n", font, TTF_GetError());

      return false;
    }

    return true;
}

/*bool Font::unloadFont(char *font)
{

}

GLuint Font::atotex(char* text, char* font,SDL_Color fontcolor, SDL_Color bgcolor)
{

}

GLuint Font::atextotex(char* text, char* font,int fontsize,SDL_Surface *texture)
{

}

SDL_Surface Font::*atosurf(char* text, char* font,int fontsize, struct colorRGBA)
{

}

SDL_Surface Font::*atextosurf(char* text, char* font,int fontsize,SDL_Surface *texture)
{

}*/

