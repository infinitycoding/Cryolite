#ifndef MODELS_H
#define MODELS_H



    #include <GL/gl.h>
    #include <GL/glu.h>

    #include "general_def.h"
    #include "types.h"
    #include "object.h"
    #include "scene.h"



    #define HOR 8
    #define VERT 16
    #define SCOPE 1
    #define GROUND_SIZE 50




    void draw_ground();
    void drawHUD();
    void createObjectTriangle(Material *mat, Scene *sce);
    void createObjectCube(Material *mat, Scene *sce);




#endif
