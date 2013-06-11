#ifndef FONT_H
#define FONT_H

/*********************************************************
 * Font-Module                                           *
 * -----------                                           *
 *                                                       *
 * Peter trys to write nice code. Really.                *
 *                                                       *
 *********************************************************/

#include <SDL_ttf.h>
#include <GL/glu.h>
#include <SDL.h>

#include <types.h>
#include <List.h>

#define MAX_NAMELENGTH 20


bool sdl_ttf_loaded = false;        // shows  if sdl_ttf is loaded yet (to prevent whatever would happen)

struct fontEntry
{
    char name[MAX_NAMELENGTH];
    int ptsize;
    TTF_Font *font;
};

struct patternFont
{
    List<struct patternEntry> *patterns;
    int numofPatterns;
    char name[MAX_NAMELENGTH];
};

struct patternEntry
{
  char character;
  SDL_Surface *pattern;
};


class Font
{
    public:
        Font();
        ~Font();

        bool loadTTF(char *font,char *name, int ptsize);
        bool unloadTTF(char *name);

        GLuint atotex(char *text, char *font,SDL_Color fontcolor, SDL_Color bgcolor);
        GLuint atextotex(char *text, char *font,int fontsize,SDL_Surface *texture);
        SDL_Surface *atosurf(char *text, char *font,int fontsize, struct colorRGBA);
        SDL_Surface *atextosurf(char *text, char *font,int fontsize,SDL_Surface *texture);

        void TTFListCleaner(struct fontEntry *element);
        void PatternFontListCleaner(struct patternFont *element);


        List<struct fontEntry> *TrueTypeFonts;          // The list of loaded truetype-fonts
        List<struct patternFont> *PatternFonts;         // The list of loaded pattern-fonts
};


#endif
