#include <GL/gl.h>
#include <GL/glu.h>
#include "include/scene.h"
#include "include/object.h"
#include <math.h>

extern float averageFPS;


Scene::Scene()
{
    this->objectList = ListCreate();
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
                    if(currentObject->distance.x>0 || currentObject->distance.z>0 || currentObject->distance.z>0)
                    {
                        int remFrames = ((int)((double)(sqrt((currentObject->distance.x*currentObject->distance.x)+(currentObject->distance.y*currentObject->distance.y)+(currentObject->distance.z*currentObject->distance.z))/(currentObject->velocity+currentObject->acceleration*(SDL_GetTicks()-currentObject->startTime)))*averageFPS));

                        double motion[3] = {currentObject->distance.x/remFrames,currentObject->distance.y/remFrames,currentObject->distance.z/remFrames};

                        if(motion[0]<0)
                            currentObject->distance.x += motion[0];
                        else
                            currentObject->distance.x -= motion[0];

                        if(motion[1]<0)
                            currentObject->distance.y += motion[1];
                        else
                            currentObject->distance.y -= motion[1];

                        if(motion[2]<0)
                            currentObject->distance.z += motion[2];
                        else
                            currentObject->distance.z -= motion[2];

                        currentObject->position.x +=motion[0];
                        currentObject->position.y +=motion[1];
                        currentObject->position.z +=motion[2];
                    }
                    else if(currentObject->velocity)
                    {
                        currentObject->position.x = currentObject->destPos.x;
                        currentObject->position.y = currentObject->destPos.y;
                        currentObject->position.z = currentObject->destPos.z;
                        currentObject->velocity = 0;
                        printf("FPS:%.1f RemF: 0 X: %f Y: %f Z: %f\n",averageFPS,currentObject->position.x,currentObject->position.y,currentObject->position.z);
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
                        printf("FPS: %f Angle %f\n",averageFPS,currentObject->Angle);

                    }

                    glRotatef(currentObject->Angle, currentObject->rotationAxis.x, currentObject->rotationAxis.y, currentObject->rotationAxis.z);
                    glTranslatef(currentObject->position.x,currentObject->position.y,currentObject->position.z); //move to local (0/0/0)
                    glScalef(currentObject->scale.x,currentObject->scale.z,currentObject->scale.z);
                    //Render Triangles
                    if(!ListIsEmpty(currentObject->triangles))
                    {
                        glBegin( GL_TRIANGLES );

                        glColor4f(currentObject->colorKey.red, currentObject->colorKey.green, currentObject->colorKey.blue, currentObject->colorKey.transparency);

                        ListSetFirst(currentObject->triangles);
                        while(!ListIsLast(currentObject->triangles))
                        {

                            struct triangle *currentTriangle = (struct triangle *)ListGetCurrent(currentObject->triangles);
                            for(int i=0;i<3;i++)
                            {
                                if(currentObject->ObjectMaterial)
                                    if(currentObject->ObjectMaterial->textureGL)
                                        glTexCoord2i( currentTriangle->texVertex[i]->x, currentTriangle->texVertex[i]->y );
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
                                        glTexCoord2i( currentSquare->texVertex[i]->x, currentSquare->texVertex[i]->y );
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
