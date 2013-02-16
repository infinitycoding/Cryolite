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


int main(void){

    screen = init_SDL(640,480,SDL_OPENGL,"Cryolite Enigen");


    glClearColor( 0.0, 0.0, 0.0, 0.0 );     // Sets the background color.
    glEnable( GL_DEPTH_TEST );


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 6.5 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_BLEND);


    glTranslatef(0,0,-3.5);


    vertex position;
    position.x = 0;
    position.y = 0;
    position.z = 0;


    struct object *pyramid = loadObject("pyramid.dat");
    if(pyramid == NULL) exit(-2);



    while(1){ //render
        process_events();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderObject(pyramid, &position);
        //draw_cube();

        rotation_handler();
        SDL_GL_SwapBuffers();

    }

}


