#ifndef LEVEL_H
#define LEVEL_H
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



#include <object.h>
#include <camera.h>
#include <light.h>
#include <fps.h>

#include <physics/PhysicsEngine.h>
#include <physics/collision.h>
#include <util/List.h>

class Level
{
    public:

        Level(void);
        ~Level(void);

        void addObject(Object *obj);
        int removeObject(Object *obj);
        void addCam(Camera *cam);
        int removeCam(Camera *cam);
        void addLamp(Lamp *L);
        int removeLamp(Lamp *L);

        void render(void);
        int handleCams(ListIterator<Camera> *c);

        FPS *fps;

        List<Object> *objectList;
        List<Camera> *Camlist;
        List<Lamp> *globalLamps;

        bool currentScene;
        GlobalLight *GlobalAmbience;


    private:
        void renderPolygones(Object *currentObject);
        void resetLights(void);

        LightManager *LM;
        CollisionList *collisions;
};



#endif
