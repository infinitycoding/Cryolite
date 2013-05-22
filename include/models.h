#ifndef MODELS_H
#define MODELS_H



#include <GL/gl.h>
#include <GL/glu.h>

#include "general_def.h"
#include "types.h"
#include "object.h"
#include "scene.h"


    void draw_ground();
    void draw_cube();
    void draw_another_cube();
    void drawHUD();
    void createObjectTriangle(Material *mat, Scene *sce);

    #define GROUND_SIZE 50



#endif
