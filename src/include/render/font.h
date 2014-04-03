#ifndef FONT_H
#define FONT_H

/*********************************************************
 * Font-Module                                           *
 * -----------                                           *
 *                                                       *
 * Peter trys to write nice code. Really.                *
 *                                                       *
 *********************************************************/

#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <List.h>

#define MAX_NAMELENGTH 20
#define STANDART_FCOLOR {255, 255, 255, 0}
#define STANDART_BGCOLOR {0, 0, 0, 0}



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

        bool loadTTF(const char *font,const char *name, int ptsize);
        bool unloadTTF(const char *name);

        GLuint surftotex(SDL_Surface *surf);

        GLuint atotex(const char *text, const char *fontname);
        GLuint atotex(const char *text, const char *fontname, SDL_Color fontcolor);
        GLuint atotex(const char *text, const char *fontname, SDL_Color fontcolor, SDL_Color backgroundcolor);

        SDL_Surface *atosurf(const char *text, const char *fontname);
        SDL_Surface *atosurf(const char *text, const char *fontname, SDL_Color fontcolor);
        SDL_Surface *atosurf(const char *text, const char *fontname, SDL_Color fontcolor, SDL_Color backgroundcolor);

        static void TTFListCleaner(struct fontEntry *element);              // The cleaner for the TTF-Lit
        static void PatternFontListCleaner(struct patternFont *element);    // The cleaner for the Pattern-Font-List


    private:
        static unsigned int numOfFontObjects;

        List<struct fontEntry> *TrueTypeFonts;          // The list of loaded truetype-fonts
        List<struct patternFont> *PatternFonts;         // The list of loaded pattern-fonts
};


#endif
