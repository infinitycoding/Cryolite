#include <models.h>
#include <material.h>
#include <font.h>

Object *iccube;
Object *gravelcube;


void INIT_Models(Level *lvl)
{
    Font stdFonts = Font();
    stdFonts.loadTTF(FONT(arial.ttf), "stdarial", 10);
    BoundBox *bb = NULL;
    BoundSphere *bs = NULL;

    bb = new BoundBox;
    bb->base.setvalue(-1, -1, -1);
    bb->width.setvalue(2, 0, 0);
    bb->height.setvalue(0, 2, 0);
    bb->length.setvalue(0, 0, 2);
    iccube = new Object(OBJECT(iccube.obj), "iccube", vector(0, 0, 0));
    iccube->objType->boundBoxes->PushFront(bb);
    lvl->addObject(iccube);

    Object *ground = new Object(OBJECT(ground.obj), "ground", vector(0, -3, 0));
    lvl->addObject(ground);

    Object *sphere = new Object(OBJECT(sphere.obj), "Sphere", vector(0, 0, 0));
    sphere->scale.setvalue(5, 5, 5);
    sphere->relativeToObject = iccube;
    lvl->addObject(sphere);

    /*bs = new BoundSphere;
    bs->center.setvalue(0, 0, 0);
    bs->radian = 1.73205;
    Object *woodcube = new Object(OBJECT(bettercube.obj), "Cube", vector(5, 0, 0));
    woodcube->objType->boundSpheres->PushFront(bs);
    lvl->addObject(woodcube);

    bs = new BoundSphere;
    bs->center.setvalue(0, 0, 0);
    bs->radian = 1.73205;
    gravelcube = new Object(OBJECT(cube.obj), "cube.001", vector(-5, 0, 0));
    gravelcube->objType->boundSpheres->PushFront(bs);
    //gravelcube->objType->ObjectTypeMaterial->ambiantTexture->nr = stdFonts.atotex("Test!\n", "stdarial");
    lvl->addObject(gravelcube);*/
}
