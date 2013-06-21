#include <font.h>


unsigned int Font::numOfFontObjects;

// The standart constructor.
// It inits sdl_ttf if is not initialized yet, creates the lists and sets the list cleaners.

Font::Font()
{
    numOfFontObjects++;

    if(numOfFontObjects == 1)
             if(TTF_Init() != 0)
                exit(-1);

    TrueTypeFonts = new List<struct fontEntry>;
    PatternFonts = new List<struct patternFont>;

    TrueTypeFonts->structCleaner = TTFListCleaner;
    PatternFonts->structCleaner = PatternFontListCleaner;
}


// The destuctor.
// It deletes the lists.

Font:: ~Font()
{
    numOfFontObjects--;

    if(numOfFontObjects == 0)
        TTF_Quit();

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


// This function converts a sdl-surface to a texture.
// You need to give to it the sdl-surface.
// It returns the number of the texture.

GLuint Font::surftotex(SDL_Surface *surf)
{
    GLuint texture;

    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &texture );

    glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D( GL_TEXTURE_2D, 0, 2, surf->w, surf->h, 0,GL_RGB, GL_UNSIGNED_BYTE, surf->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    printf("texur %d created\n",texture);

    return texture;
}


GLuint Font::atotex(char *text, char *fontname)
{
    return surftotex(atosurf(text, fontname));      // first convert ascii to surface and then convert surface to texture
}


GLuint Font::atotex(char *text, char *fontname, SDL_Color fontcolor)
{
    return surftotex(atosurf(text, fontname, fontcolor));   // first convert ascii to surface and then convert surface to texture
}


GLuint Font::atotex(char *text, char *fontname, SDL_Color fontcolor, SDL_Color backgroundcolor)
{
    return surftotex(atosurf(text, fontname, fontcolor, backgroundcolor));
}


// This function converts a text and a font to a sdl-surface.
// You need to give to it the text and the fontname.
// It uses the standart fontcolor and the standart backgroundcolor.

SDL_Surface *Font::atosurf(char *text, char *fontname)
{
    SDL_Color fcolor = STANDART_FCOLOR;     // i need this because there are no SDL_Color constants
    SDL_Color bgcolor = STANDART_BGCOLOR;   // i need this because there are no SDL_Color constants

    return atosurf(text, fontname, fcolor, bgcolor);    // give the job to the big function (so i don't need to write it three times)
}


// This function converts a text and a font to a sdl-surface.
// You need to give to it the text, the fontname and the fontcolor.
// It uses the standart backgroundcolor.

SDL_Surface *Font::atosurf(char *text, char *fontname, SDL_Color fontcolor)
{
    SDL_Color bgcolor = STANDART_BGCOLOR;   // i need this because there are no SDL_Color constants

    return atosurf(text, fontname, fontcolor, bgcolor); // give the job to the big function (so i don't need to write it three times)
}


// This function converts a text and a font to a sdl-surface.
// You need to give to it the text, the fontname, the fontcolor and the backgroundcolor.

SDL_Surface *Font::atosurf(char *text, char *fontname, SDL_Color fontcolor, SDL_Color backgroundcolor)
{
    bool found_font = false;               // shows me after searching loop if i found the correct font

    struct fontEntry *fontToUse;           // the font in which the text will be printed

    if(TrueTypeFonts->ListIsEmpty())        // first check if the list is empty
    {
        fprintf(stderr, "There is no font loaded, so it's impossible to use one. \n");
        return false;
    }

    TrueTypeFonts->ListSetFirst();          // start at the beginning of the list with the search

    while(!(TrueTypeFonts->ListIsLast()))     // searching loop
    {
        fontToUse = TrueTypeFonts->ListGetCurrent();    // get the actual element

        if(!strncmp(fontToUse->name, fontname, MAX_NAMELENGTH))         // check if it's the correct one
        {
            found_font = true;
            break;
        }

        TrueTypeFonts->ListNext();          // set the current pointer to the next element
    }

    if(found_font == false)                 // end function if the font is not in the list
    {
        fprintf(stderr, "The font could not be used, because it's not loaded. \n");
        return false;
    }



    return TTF_RenderText_Shaded(fontToUse->font, text, fontcolor, backgroundcolor);   // the main converting function is called
}


void Font::TTFListCleaner(struct fontEntry *element)
{
    TTF_CloseFont(element->font);
}


void Font::PatternFontListCleaner(struct patternFont *element)
{
    delete element->patterns;
}

