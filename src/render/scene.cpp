#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"
#include "object.h"
#include <math.h>
#include <SDL.h>



Scene::Scene()
{
    this->objectList = ListCreate();
    currenttick = 0;
    ticcount = 0;
    tickbundle = 3;
    sum = 0;
    lasttick = SDL_GetTicks();
    accuracy = 60;

}

Scene::~Scene()
{
    ListSetFirst(this->objectList);
    while(!ListIsLast(this->objectList))
    {
        ListRemove(this->objectList);
        ListNext(this->objectList);
    }
    free(this->objectList);
}


void Scene::addObject(Object *obj)
{
    ListPushFront(this->objectList,obj);
}

int Scene::removeObject(char *name)
{
    int delObj = 0;
    ListSetFirst(this->objectList);
    while(!ListIsLast(this->objectList))
    {
        Object *currentObject = (Object *)ListGetCurrent(this->objectList);
        if(!strncmp(currentObject->objectname,name,20))
        {
            ListRemove(this->objectList);
            delObj++;
        }
        ListNext(this->objectList);
    }
    return delObj;
}

int Scene::removeObject(Object *obj)
{
    int delObj = 0;
    ListSetFirst(this->objectList);
    while(!ListIsLast(this->objectList))
    {
        if(ListGetCurrent(this->objectList) == obj)
        {
            ListRemove(this->objectList);
            delObj++;
        }
        ListNext(this->objectList);
    }
    return delObj;
}

void Scene::render()
{
    this->calculateFPS();
    if(!ListIsEmpty(this->objectList))
    {
        glMatrixMode(GL_MODELVIEW);
        ListSetFirst(this->objectList);

        while(!ListIsLast(this->objectList))
        {
            Object *currentObject = (Object *)ListGetCurrent(this->objectList);
            if(!ListIsEmpty(currentObject->vertices))
            {
                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                    if(currentObject->ObjectMaterial)
                        glBindTexture( GL_TEXTURE_2D, currentObject->ObjectMaterial->textureGL);
                    else
                        glBindTexture( GL_TEXTURE_2D, 0);
                    //Modify Model Matrix
                    if(currentObject->Lmr>0)
                    {
                        double MPF = (double)(currentObject->Vm+currentObject->Am*(SDL_GetTicks()-currentObject->Tms))/averageFPS;
                        currentObject->Lmr -= MPF;
                        currentObject->position.x += currentObject->Dm.x*MPF;
                        currentObject->position.y += currentObject->Dm.y*MPF;
                        currentObject->position.z += currentObject->Dm.z*MPF;

                    }
                    else if(currentObject->Vm)
                    {
                        currentObject->position = currentObject->Pmd;
                        currentObject->Dm.x = 0;
                        currentObject->Dm.y = 0;
                        currentObject->Dm.z = 0;
                        currentObject->Lmr = 0;
                        currentObject->Vm = 0;
                        currentObject->Am = 0;
                        currentObject->Tms = 0;

                        printf("RemF: 0 X: %f Y: %f Z: %f\n",currentObject->position.x,currentObject->position.y,currentObject->position.z);
                    }

                    if(currentObject->remeaningAngle*currentObject->remAngleSing>0)
                    {
                        double APF = (double)(currentObject->rotationVelocity+currentObject->rotationAcceleration*(SDL_GetTicks()-currentObject->startRotationTime))/averageFPS;
                        currentObject->remeaningAngle -=APF;
                        currentObject->Angle += APF;
                    }
                    else if(currentObject->rotationVelocity)
                    {
                        currentObject->Angle = currentObject->destAngle;
                        currentObject->rotationVelocity = 0;
                        currentObject->rotationAcceleration = 0;
                        currentObject->remeaningAngle = 0;
                        printf("Angle: %f\n",currentObject->Angle);

                    }

                    glRotatef(currentObject->Angle, currentObject->rotationAxis.x, currentObject->rotationAxis.y, currentObject->rotationAxis.z);
                    glTranslatef(currentObject->position.x,currentObject->position.y,currentObject->position.z); //move to local (0/0/0)
                    glScalef(currentObject->scale.x,currentObject->scale.z,currentObject->scale.z);
                    //Render Triangles
                    if(!ListIsEmpty(currentObject->triangles))
                    {
                        glBegin( GL_TRIANGLES );

                        ListSetFirst(currentObject->triangles);
                        while(!ListIsLast(currentObject->triangles))
                        {

                            struct triangle *currentTriangle = (struct triangle *)ListGetCurrent(currentObject->triangles);
                            for(int i=0;i<3;i++)
                            {
                                if(currentObject->ObjectMaterial)
                                    if(currentObject->ObjectMaterial->textureGL)
                                        glTexCoord2f( currentTriangle->texVertex[i]->x, currentTriangle->texVertex[i]->y );
                                glVertex3f( currentTriangle->objVertex[i]->x, currentTriangle->objVertex[i]->y, currentTriangle->objVertex[i]->z);

                            }
                            ListNext(currentObject->triangles);
                        }

                        glEnd();

                    }
                    //Render Quads
                    if(!ListIsEmpty(currentObject->squares))
                    {
                        glBegin( GL_QUADS );
                        ListSetFirst(currentObject->squares);
                        while(!ListIsLast(currentObject->squares))
                        {
                            struct square *currentSquare = (struct square *)ListGetCurrent(currentObject->squares);
                            for(int i=0;i<4;i++)
                            {
                                if(currentObject->ObjectMaterial)
                                    if(currentObject->ObjectMaterial->textureGL)
                                        glTexCoord2f( currentSquare->texVertex[i]->x, currentSquare->texVertex[i]->y );
                                glVertex3f( currentSquare->objVertex[i]->x, currentSquare->objVertex[i]->y, currentSquare->objVertex[i]->z);
                            }
                            ListNext(currentObject->squares);
                        }
                        glEnd();

                    }


                glPopMatrix();
                ListNext(this->objectList);
            }
        }
    }
}


void Scene::renderQuad(void)
{

}


void Scene::calculateFPS(void)
{
    currenttick = SDL_GetTicks();
    if(ticcount==tickbundle)
    {
        averageFPS = sum/tickbundle;
        sum = 0;
        ticcount = 0;
        tickbundle = accuracy;
    }
    else
    {
        if(currenttick-lasttick > 0)
            sum +=(1000.0/(float)(currenttick-lasttick));
            ticcount++;
    }
    lasttick = currenttick;
}
