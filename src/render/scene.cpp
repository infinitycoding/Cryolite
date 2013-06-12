#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <SDL.h>

#include <scene.h>
#include <object.h>




Scene::Scene()
{
    this->objectList = new List<Object>;
    currenttick = 0;
    ticcount = 0;
    tickbundle = 3;
    sum = 0;
    lasttick = SDL_GetTicks();
    accuracy = 60;

}

Scene::~Scene()
{
    this->objectList->ListSetFirst();
    while(!this->objectList->ListIsLast())
    {
        this->objectList->ListRemove();
        this->objectList->ListNext();
    }
    delete this->objectList;
}


void Scene::addObject(Object *obj)
{
    this->objectList->ListPushFront(obj);
}

int Scene::removeObject(char *name)
{
    int delObj = 0;
    this->objectList->ListSetFirst();
    while(!this->objectList->ListIsLast())
    {
        Object *currentObject = (Object *)this->objectList->ListGetCurrent();
        if(!strncmp(currentObject->objectname,name,20))
        {
            this->objectList->ListRemove();
            delObj++;
        }
        this->objectList->ListNext();
    }
    return delObj;
}

int Scene::removeObject(Object *obj)
{
    int delObj = 0;
    this->objectList->ListSetFirst();
    while(!this->objectList->ListIsLast())
    {
        if(this->objectList->ListGetCurrent() == obj)
        {
            this->objectList->ListRemove();
            delObj++;
        }
        this->objectList->ListNext();
    }
    return delObj;
}

void Scene::render()
{
    this->calculateFPS();
    if(!this->objectList->ListIsEmpty())
    {
        glMatrixMode(GL_MODELVIEW);
        this->objectList->ListSetFirst();

        while(!this->objectList->ListIsLast())
        {
            Object *currentObject = (Object *)this->objectList->ListGetCurrent();
            if(!currentObject->vertices->ListIsEmpty())
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
                        double MPF = (double)(currentObject->Vm+currentObject->Am*((SDL_GetTicks()-currentObject->Tms)/1000))/averageFPS;
                        currentObject->Lmr -= MPF;
                        currentObject->position = (currentObject->position) + (currentObject->Dm * MPF);
                    }
                    else if(currentObject->Vm)
                    {
                        currentObject->position = currentObject->Pmd;
                        currentObject->Dm.null();
                        currentObject->Lmr = 0;
                        currentObject->Vm = 0;
                        currentObject->Am = 0;
                        currentObject->Tms = 0;

                        printf("RemF: 0 X: %f Y: %f Z: %f\n",currentObject->position.elements[0],currentObject->position.elements[1],currentObject->position.elements[2]);
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

                    glRotatef(currentObject->Angle, currentObject->rotationAxis.elements[0], currentObject->rotationAxis.elements[1], currentObject->rotationAxis.elements[2]);
                    glTranslatef(currentObject->position.elements[0],currentObject->position.elements[1],currentObject->position.elements[2]); //move to local (0/0/0)
                    glScalef(currentObject->scale.elements[0],currentObject->scale.elements[1],currentObject->scale.elements[2]);
                    //Render Triangles
                    if(!currentObject->triangles->ListIsEmpty())
                    {
                        glBegin( GL_TRIANGLES );

                        currentObject->triangles->ListSetFirst();
                        while(!currentObject->triangles->ListIsLast())
                        {

                            struct triangle *currentTriangle = (struct triangle *)currentObject->triangles->ListGetCurrent();
                            for(int i=0;i<3;i++)
                            {
                                if(currentObject->ObjectMaterial)
                                    if(currentObject->ObjectMaterial->textureGL)
                                        glTexCoord2f( currentTriangle->texVertex[i]->x, currentTriangle->texVertex[i]->y );
                                glVertex3f( currentTriangle->objVertex[i]->x, currentTriangle->objVertex[i]->y, currentTriangle->objVertex[i]->z);

                            }
                            currentObject->triangles->ListNext();
                        }

                        glEnd();

                    }
                    //Render Quads
                    if(!currentObject->squares->ListIsEmpty())
                    {
                        glBegin( GL_QUADS );
                        currentObject->squares->ListSetFirst();
                        while(!currentObject->squares->ListIsLast())
                        {
                            struct square *currentSquare = (struct square *)currentObject->squares->ListGetCurrent();
                            for(int i=0;i<4;i++)
                            {
                                if(currentObject->ObjectMaterial)
                                    if(currentObject->ObjectMaterial->textureGL)
                                        glTexCoord2f( currentSquare->texVertex[i]->x, currentSquare->texVertex[i]->y );
                                glVertex3f( currentSquare->objVertex[i]->x, currentSquare->objVertex[i]->y, currentSquare->objVertex[i]->z);
                            }
                            currentObject->squares->ListNext();
                        }
                        glEnd();

                    }


                glPopMatrix();
                this->objectList->ListNext();
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
