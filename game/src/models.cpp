/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

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
