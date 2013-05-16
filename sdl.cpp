#include "include/sdl.h"

SDL_Surface* init_SDL(int width, int height, int flags, const char* caption){
    const SDL_VideoInfo *info = NULL;
    SDL_Surface* screen = NULL;
    if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
    {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        exit(-1);
    }

    atexit(SDL_Quit);                   // Quit SDL if the programm ends.

    info = SDL_GetVideoInfo();

    if( !info )
    {
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        exit(-1);
    }

    SDL_WM_SetCaption( caption, NULL );

    int bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    screen = SDL_SetVideoMode( width, height, bpp, flags);
    if(  screen == NULL ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(-1);
    }
    return screen;
}

GLuint loadTexture2D(const char* file){
    GLuint texture;
    GLint  nOfColors;
    GLenum texture_format;
    SDL_Surface* textureBMP = IMG_Load(file);
    if(textureBMP == 0)
    {
        printf("textur %s not found",file);
        return 0;
    }
    	if ( (textureBMP->w & (textureBMP->w - 1)) != 0 ) {
		printf("warning: %s's width is not a power of 2\n",file);
	}
	if ( (textureBMP->h & (textureBMP->h - 1)) != 0 ) {
		printf("warning: %s's height is not a power of 2\n",file);
	}
        nOfColors = textureBMP->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (textureBMP->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (textureBMP->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: %s is not truecolor..  this will probably break\n",file);
        }
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, textureBMP->w, textureBMP->h, 0,texture_format, GL_UNSIGNED_BYTE, textureBMP->pixels );

    return texture;
}

