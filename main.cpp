#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL_thread.h>
#include <SDL_image.h>

#include "include/object.h"
#include "include/sdl.h"
#include "include/modelview.h"

void menue(void);

SDL_Surface* screen = NULL;
GLuint texture;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
GLenum texture_format;
GLint  nOfColors;
SDL_Surface* textureBMP;
void draw_cube()
{
glBindTexture( GL_TEXTURE_2D, texture );

    glBegin( GL_QUADS );

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 0 );
          glVertex3f(-1, 1, 1);
          glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, 1);
          glTexCoord2i( 1, 1 );
          glVertex3f( 1, -1, 1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, -1, -1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, -1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f( 1, -1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f( 1, -1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, -1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, -1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, -1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, -1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f(-1, -1, -1);
        glTexCoord2i( 0, 0 );
          glVertex3f(-1, -1, 1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, 1, 1);
        glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, -1);

        glTexCoord2i( 1, 0 );
          glVertex3f( 1, 1, 1);
        glTexCoord2i( 0, 0 );
          glVertex3f( 1, 1, -1);
        glTexCoord2i( 0, 1 );
          glVertex3f(-1, 1, -1);
          glTexCoord2i( 1, 1 );
          glVertex3f(-1, 1, 1);

  glEnd();

}



int main(int argc, char *argv[]){

    //menue();

    screen = init_SDL(640,480,SDL_OPENGL,"Cryolite Engine");


    glClearColor( 0.0, 0.0, 0.0, 0.0 ); // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 6.5 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_BLEND);


    glTranslatef(0,0,-3.5);


    /*struct vertex position;
    position.x = 0;
    position.y = 0;
    position.z = 0;


    struct object *entity;

    if(argc > 1)
        entity = loadObject(argv[1]);
    else
    {
        char file_name[100];

        printf("Name der Datei: ");
        scanf("%s", file_name);

        entity = loadObject(file_name);
    }

    if(entity == NULL) exit(-2);*/

    textureBMP = SDL_LoadBMP("textur.bmp");
    if(textureBMP == 0)
    {
        printf("textur nicht gefunden!!");
        SDL_Quit();
        exit(1);
    }
    	if ( (textureBMP->w & (textureBMP->w - 1)) != 0 ) {
		printf("warning: image.bmp's width is not a power of 2\n");
	}

	// Also check if the height is a power of 2
	if ( (textureBMP->h & (textureBMP->h - 1)) != 0 ) {
		printf("warning: image.bmp's height is not a power of 2\n");
	}

        // get the number of channels in the SDL surface
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
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }

	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );

	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, textureBMP->w, textureBMP->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, textureBMP->pixels );
    glEnable( GL_TEXTURE_2D );




    while(1){ //render
        process_events();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //renderObject(entity, &position);
        draw_cube();

        rotation_handler();
        SDL_GL_SwapBuffers();

    }

}

