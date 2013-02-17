#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL_thread.h>

#include "include/object.h"
#include "include/sdl.h"
#include "include/modelview.h"

void menue(void);

SDL_Surface* screen = NULL;

void draw_cube()
{
    glBegin( GL_QUADS );

        glColor3f(1, 0,   0  );
          glVertex3f( 1,  1, -1);
          glVertex3f( 1, -1, -1);
          glVertex3f(-1, -1, -1);
          glVertex3f(-1,  1, -1);

        glColor3f(0, 1,   0  );
          glVertex3f( 1,  1,  1);
          glVertex3f(-1,  1,  1);
          glVertex3f(-1, -1,  1);
          glVertex3f( 1, -1,  1);

        glColor3f(0, 0,   1  );
          glVertex3f( 1,  1, -1);
          glVertex3f( 1,  1,  1);
          glVertex3f( 1, -1,  1);
          glVertex3f( 1, -1, -1);

        glColor3f(1, 1,   0  );
          glVertex3f( 1, -1, -1);
          glVertex3f( 1, -1,  1);
          glVertex3f(-1, -1,  1);
          glVertex3f(-1, -1, -1);

        glColor3f(0, 0.5, 1  );
          glVertex3f(-1, -1, -1);
          glVertex3f(-1, -1,  1);
          glVertex3f(-1,  1,  1);
          glVertex3f(-1,  1, -1);

        glColor3f(1, 0.1, 0.8);
          glVertex3f( 1,  1,  1);
          glVertex3f( 1,  1, -1);
          glVertex3f(-1,  1, -1);
          glVertex3f(-1,  1,  1);

  glEnd();
}

int main(int argc, char *argv[]){

    menue();

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


    struct vertex position;
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

    if(entity == NULL) exit(-2);

    while(1){ //render
        process_events();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderObject(entity, &position);
        //draw_cube();

        rotation_handler();
        SDL_GL_SwapBuffers();

    }

}

