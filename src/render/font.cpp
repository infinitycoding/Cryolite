#include <font.h>

// The standart constructor.
// It inits sdl_ttf if is not initialized yet, creates the lists and sets the list cleaners.

Font::Font()
{
    if(sdl_ttf_loaded == false)     // to don't double load sdl_ttf
    {
        sdl_ttf_loaded = true;

        if (TTF_Init() == -1)       // initialize and exit if it fails
        {
            fprintf(stderr, "Could not initialize SDL_ttf: %s \n", TTF_GetError());
            exit(-1);
        }
    }

    TrueTypeFonts = new List<struct fontEntry>;
    PatternFonts = new List<struct patternFont>;

    // TODO: Set list cleaners
}

// The destuctor.
// It deletes the lists.

Font:: ~Font()
{
    delete TrueTypeFonts;
    delete PatternFonts;
}

// This function loads a truetype-font from a file and pushs it into the list.
// You need to give the filename, the intern fontname and the pointsize to it.
// It returns if the function is completed successfully or not.

bool Font::loadTTF(char *font, char *name, int ptsize)
{
    TTF_Font* font_ptr;              // the font handle
    struct fontEntry *new_font;     // the complete font


    if ((font_ptr = TTF_OpenFont(font, ptsize)) == NULL)        // load font and catch errors
    {
        fprintf(stderr, "Could not load font: %s %s \n", font, TTF_GetError());
        return false;
    }

    new_font = new fontEntry;       // alloc memory for the new font

    new_font->font = font_ptr;          // set the font handle of the new font
    new_font->ptsize = ptsize;          // set the pointsize of the new font
    strncpy(new_font->name, name, MAX_NAMELENGTH);  // set the name of the new font

    TrueTypeFonts->ListPushFront(new_font);     // push the new font in the ttf-list

    return true;
}

// This function unloads a truetype-font from the list.
// You need to give the intern fontname to it.
// It returns if the function is completed successfully or not.

bool Font::unloadTTF(char *name)
{
    bool found_font = false;                // shows me after searching loop if i found the correct font
    struct fontEntry *font_for_deletion;    // a pointer to the font the function should unload


    if(TrueTypeFonts->ListIsEmpty())        // first check if the list is empty
    {
        fprintf(stderr, "There is no font loaded, so it's impossible to unload one. \n");
        return false;
    }

    TrueTypeFonts->ListSetFirst();          // start at the beginning of the list with the search

    while(!(TrueTypeFonts->ListIsLast()))     // searching loop
    {
        font_for_deletion = TrueTypeFonts->ListGetCurrent();    // get the actual element

        if(!strncmp(font_for_deletion->name, name, MAX_NAMELENGTH))         // check if it's the correct one
        {
            found_font = true;
            break;
        }

        TrueTypeFonts->ListNext();          // set the current pointer to the next element
    }

    if(found_font == false)                 // end function if the font is not in the list
    {
        fprintf(stderr, "The font could not be unloaded, because it's not loaded. \n");
        return false;
    }

    TTF_CloseFont(font_for_deletion->font); // close the font (don't know why, maybe it is important)
    TrueTypeFonts->ListRemove();            // remove the font out of the list
    delete font_for_deletion;              // free the ram

    return true;
}

/*GLuint Font::atotex(char* text, char* font,SDL_Color fontcolor, SDL_Color bgcolor)
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

void Font::TTFListCleaner(struct fontEntry *element)
{
    TTF_CloseFont(element->font);
}

void PatternFontListCleaner(struct patternFont *element)
{
    delete element->patterns;
}

