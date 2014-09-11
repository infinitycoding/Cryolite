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


#include <level.h>


Level::Level(void)
{
    fps = new FPS();
    objectList = new List<Object>;
    Camlist = new List<Camera>;
    globalLamps = new List<Lamp>;
    LM = new LightManager();
    collisions = new CollisionList(objectList);
    GlobalAmbience = NULL;
}

Level::~Level()
{
    delete objectList;
    delete Camlist;
    delete globalLamps;
    delete LM;
    delete collisions;
}


void Level::addObject(Object *obj)
{
    this->objectList->PushFront(obj);
}

int Level::removeObject(Object *obj)
{
    int delObj = 0;
    ListIterator<Object> i = *ListIterator<Object>(objectList).SetFirst();
    while(!i.IsLast())
    {
        if(i.GetCurrent() == obj)
        {
            i.Remove();
            delObj++;
        }
        i.Next();
    }
    return delObj;
}

void Level::addCam(Camera *cam)
{
    Camlist->PushFront(cam);
}

int Level::removeCam(Camera *cam)
{
    int delCams = 0;
    ListIterator<Camera> C = *ListIterator<Camera>(Camlist).SetFirst();
    while(!C.IsLast() && C.IsEmpty())
    {
        if(C.GetCurrent() == cam)
        {
            C.Remove();
            delCams++;
        }
        C.Next();
    }
    return delCams;
}

void Level::addLamp(Lamp *L)
{
    globalLamps->PushFront(L);
    L->Lightnum = LM->getLightNum();
    L->reg = true;
    L->refresh();
}

int Level::removeLamp(Lamp *L)
{
    int delLamps = 0;
    ListIterator<Lamp> I = *ListIterator<Lamp>(globalLamps).SetFirst();
    while(!I.IsLast() && I.IsEmpty())
    {
        if(I.GetCurrent() == L)
        {
            I.Remove();
            L->reg = false;
            LM->returnLightNum(L->Lightnum);
            L->Lightnum = 0;
            delLamps++;
        }
        I.Next();
    }
    return delLamps;

}
