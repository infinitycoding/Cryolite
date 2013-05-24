#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <GL/glu.h>
#include <SDL.h>
#include "types.h"

struct fontEntry
{
    char name[20];
    TTF_Font *font;
};

struct patternFont
{
    struct List *patterns;
    int numofPatterns;
    char name[20];
};

struct patternEntry
{
  char character;
  SDL_Surface *pattern;
};


class Font
{
    public:
        Font(char *font);
        Font();
        ~Font();
        bool LoadFont(char *font);
        bool unloadFont(char *font);
        GLuint atotex(char* text, char* font,int fontsize,struct colorRGBA );
        GLuint atextotex(char* text, char* font,int fontsize,SDL_Surface *texture);
        SDL_Surface *atosurf(char* text, char* font,int fontsize, struct colorRGBA);
        SDL_Surface *atextosurf(char* text, char* font,int fontsize,SDL_Surface *texture);

        struct List *TrueTypeFonts;
        struct List *PatternFonts;
};


#endif
