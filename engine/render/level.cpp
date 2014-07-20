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

void Level::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(GlobalAmbience && !currentScene)
        GlobalAmbience->activateLight();

    if(!globalLamps->IsEmpty() && !currentScene)
        resetLights();

    else if(!GlobalAmbience && globalLamps->IsEmpty())
    {
        GLboolean activlight;
        glGetBooleanv(GL_LIGHTING, &activlight);
        if(activlight)
            glDisable(GL_LIGHTING);
    }
    else
    {
        GLboolean activlight;
        glGetBooleanv(GL_LIGHTING, &activlight);
        if(!activlight)
            glEnable(GL_LIGHTING);
    }


    fps->calculate();

    // Interpolate Physics
    Object *currentObject = NULL;
    ListIterator<Object> O = *ListIterator<Object>(objectList).SetFirst();

    while(!O.IsLast())
    {
        currentObject = O.GetCurrent();
        currentObject->physObj->interpolatePhysics(&(currentObject->localPosition), fps->get());
        O.Next();
    }

    collisions->checkCollisions();

    // Debug only

    List<collision> *collList = collisions->getCollisions();
    ListIterator<collision> collIterator = *ListIterator<collision>(collList).SetFirst();
    collision *currentCollision = NULL;
    vector temp;

    while(!collIterator.IsLast())
    {
        currentCollision = collIterator.GetCurrent();

        if(!strncmp(currentCollision->obj1->objType->objectTypeName, "projectile", strlen("projectile")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with projectile %p!\n", currentCollision->obj1, currentCollision->obj2);
            removeObject(currentCollision->obj1);
            removeObject(currentCollision->obj2);
            delete currentCollision->obj1;
            delete currentCollision->obj2;
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "projectile", strlen("projectile")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "ground", strlen("ground")))
        {
            printf("Projectile %p collided with ground!\n", currentCollision->obj1);
            removeObject(currentCollision->obj1);
            delete currentCollision->obj1;
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "ground", strlen("ground")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with ground!\n", currentCollision->obj2);
            removeObject(currentCollision->obj2);
            delete currentCollision->obj2;
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "ground", strlen("ground")))
        {
            printf("Object %p collided with ground!\n", currentCollision->obj2);
            temp.setvalue(currentCollision->obj2->physObj->getImpulse().x[0], currentCollision->obj2->physObj->getImpulse().x[1], 0.0);
            currentCollision->obj2->physObj->setImpulse(temp);
        }
        else if(!strncmp(currentCollision->obj2->objType->objectTypeName, "ground", strlen("ground")))
        {
            printf("Object %p collided with ground!\n", currentCollision->obj1);
            temp.setvalue(currentCollision->obj1->physObj->getImpulse().x[0], currentCollision->obj1->physObj->getImpulse().x[1], 0.0);
            currentCollision->obj1->physObj->setImpulse(temp);
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with object %p!\n", currentCollision->obj1, currentCollision->obj2);
            currentCollision->obj2->physObj->setImpulse(currentCollision->obj1->physObj->getImpulse() + currentCollision->obj2->physObj->getImpulse());
            removeObject(currentCollision->obj1);
            delete currentCollision->obj1;
        }
        else if(!strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with object %p!\n", currentCollision->obj2, currentCollision->obj1);
            currentCollision->obj1->physObj->setImpulse(currentCollision->obj1->physObj->getImpulse() + currentCollision->obj2->physObj->getImpulse());
            removeObject(currentCollision->obj2);
            delete currentCollision->obj2;
        }
        else
        {
            printf("Object %p collided with object %p!\n", currentCollision->obj1, currentCollision->obj2);
            temp = currentCollision->obj1->physObj->getImpulse();
            currentCollision->obj1->physObj->setImpulse(currentCollision->obj2->physObj->getImpulse());
            currentCollision->obj2->physObj->setImpulse(temp);
        }

        collIterator.Next();
    }

    // Debug end

    collisions->checkCollisions();

    ListIterator<Camera> c = *ListIterator<Camera>(Camlist).SetFirst();
    while(handleCams(&c))
    {
        if(!globalLamps->IsEmpty())
        {
            ListIterator<Lamp> L(globalLamps);
            L.SetFirst();
            while(!L.IsLast())
            {
                Lamp *currentLamp = L.GetCurrent();
                if(currentLamp->activ)
                {
                    currentLamp->refreshPosition();
                }
                L.Next();
            }
        }

        if(!objectList->IsEmpty())
        {
            glMatrixMode(GL_MODELVIEW);

            O.SetFirst();
            while(!O.IsLast())
            {
                currentObject = O.GetCurrent();
                if(currentObject->objType)
                {
                    if(!currentObject->objType->vertices->IsEmpty())
                    {
                        glPushMatrix();

                            glEnable(GL_TEXTURE_2D);
                            if(currentObject->objType != NULL && currentObject->objType->ObjectTypeMaterial != NULL && currentObject->objType->ObjectTypeMaterial->ambiantTexture != NULL)
                                glBindTexture( GL_TEXTURE_2D, currentObject->objType->ObjectTypeMaterial->ambiantTexture->nr);
                            else
                                glBindTexture( GL_TEXTURE_2D, 0);


                            //Modify Model Matrix
                            glRotatef(currentObject->rot.Angle, currentObject->rot.rotationAxis.x[0], currentObject->rot.rotationAxis.x[1], currentObject->rot.rotationAxis.x[2]);
                            glTranslatef(currentObject->getPosition().x[0],currentObject->getPosition().x[1],currentObject->getPosition().x [2]);
                            glScalef(currentObject->scale.x[0],currentObject->scale.x[1],currentObject->scale.x[2]);

                            //Render Polyganes
                            if(!currentObject->objType->polygones->IsEmpty())
                                renderPolygones(currentObject);


                        glPopMatrix();

                    }
                }

                /*if(!currentObject->sounds->IsEmpty())
                {
                    ListIterator<Sound> S(currentObject->sounds);
                    S.SetFirst();
                    while(!S.IsLast() && !S.IsEmpty())
                    {
                        S.GetCurrent()->refreshPosition(listenerPosition, currentObject->getPosition());
                        S.Next();
                    }
                }*/

                O.Next();
           }
        }
    }

    currentScene = true;
}

void Level::resetLights(void)
{
    ListIterator<Lamp> L = *ListIterator<Lamp>(globalLamps).SetFirst();
    while(!L.IsLast())
    {
        if(L.GetCurrent()->activ)
            L.GetCurrent()->refresh();
        L.Next();
    }
}


int Level::handleCams(ListIterator<Camera> *c)
{

    if(!Camlist->IsEmpty() && !c->IsLast())
    {
        Camera *currentCam = c->GetCurrent();
        c->Next();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(currentCam->x,currentCam->y,currentCam->width,currentCam->height);
        gluPerspective(currentCam->fov, currentCam->width/currentCam->height, currentCam->nearClip, currentCam->farClip );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(currentCam->getPosition().x[0],currentCam->getPosition().x[1],currentCam->getPosition().x[2],currentCam->lookingDirection.x[0]+currentCam->getPosition().x[0],currentCam->lookingDirection.x[1]+currentCam->getPosition().x[1],currentCam->lookingDirection.x[2]+currentCam->getPosition().x[2],0.0,1.0,0.0);

        return true;
    }

    return false;
}

float shine[] { 0.75f, 0.75f, 0.75f, 1 };

void Level::renderPolygones(Object *currentObject)
{
    if(!currentObject->objType->polygones)
        return;
    ListIterator<Polygon> p = ListIterator<Polygon>(currentObject->objType->polygones);
    p.SetFirst();

    while(!p.IsLast())
    {
        Polygon *currentPolygon = (Polygon *)p.GetCurrent();
        glBegin( GL_POLYGON );

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentObject->objType->ObjectTypeMaterial->ambiantMatColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentObject->objType->ObjectTypeMaterial->diffuseMatColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentObject->objType->ObjectTypeMaterial->specularMatColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, currentObject->objType->ObjectTypeMaterial->emissiveMatColor);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentObject->objType->ObjectTypeMaterial->specularExponent);

            for(int i=0;i < currentPolygon->getVertexAmount();i++)
            {
                if(currentPolygon->getNormVector(i) != NULL)
                    glNormal3f(currentPolygon->getNormVector(i)->x[0],currentPolygon->getNormVector(i)->x[1],currentPolygon->getNormVector(i)->x[2]);

                if(currentObject->objType->ObjectTypeMaterial && currentObject->objType->ObjectTypeMaterial->ambiantTexture && currentPolygon->getTexVertex(i) != NULL && currentPolygon->getTexVertex(i) != NULL)
                    glTexCoord2f( currentPolygon->getTexVertex(i)->x, currentPolygon->getTexVertex(i)->y );

                if(currentPolygon->getObjVertex(i) != NULL)
                    glVertex3f( currentPolygon->getObjVertex(i)->x[0], currentPolygon->getObjVertex(i)->x[1], currentPolygon->getObjVertex(i)->x[2]);
            }

        glEnd();

        p.Next();
    }
}