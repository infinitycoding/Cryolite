#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <GL/glu.h>
#include <SDL.h>

#include <types.h>

struct fontEntry
{
    char name[20];
    int ptsize;
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

        bool LoadFont(char *font,char* name, int ptsize);
        bool unloadFont(char *font);

        GLuint atotex(char* text, char* font,SDL_Color fontcolor, SDL_Color bgcolor);
        GLuint atextotex(char* text, char* font,int fontsize,SDL_Surface *texture);
        SDL_Surface *atosurf(char* text, char* font,int fontsize, struct colorRGBA);
        SDL_Surface *atextosurf(char* text, char* font,int fontsize,SDL_Surface *texture);


        struct List *TrueTypeFonts;
        struct List *PatternFonts;
};


#endif
