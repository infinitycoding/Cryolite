#include <GL/gl.h>
#include <GL/glu.h>
#include "include/scene.h"
#include "include/object.h"



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
        if(strncmp(currentObject->objectname,name,20))
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
                    glBindTexture( GL_TEXTURE_2D, currentObject->ObjectMaterial.textureGL);
                    //Modify Model Matrix
                    glTranslatef(currentObject->position.x,currentObject->position.y,currentObject->position.z); //move to local (0/0/0)
                    glRotatef(currentObject->rotationAngle, currentObject->rotationAxis.x, currentObject->rotationAxis.y, currentObject->rotationAxis.z);
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
                                glTexCoord2i( currentTriangle->texVertex[i]->x, currentTriangle->texVertex[i]->y );
                                glVertex3f( currentTriangle->objVertex[i]->x, currentTriangle->objVertex[i]->y, currentTriangle->objVertex[i]->z);

                            }
                            ListNext(currentObject->triangles);
                        }
                        glEnd();

                    }

                    //Render Quads
                    if(!!ListIsEmpty(currentObject->squares))
                    {
                        glBegin( GL_QUADS );
                        ListSetFirst(currentObject->squares);
                        while(!ListIsLast(currentObject->squares))
                        {
                            struct square *currentSquare = (struct square *)ListGetCurrent(currentObject->squares);
                            for(int i=0;i<4;i++)
                            {
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
