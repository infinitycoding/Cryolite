#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <SDL.h>
#include <general_def.h>
#include <scene.h>
#include <object.h>




Scene::Scene()
{
    this->objectList = new List<Object>;
    this->Camlist = new List<Camera>;
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
    calculateFPS();
    this->Camlist->ListSetFirst();
    while(handleCams())
    {
        if(!objectList->ListIsEmpty())
        {
            glMatrixMode(GL_MODELVIEW);
            objectList->ListSetFirst();

            while(!objectList->ListIsLast())
            {
                Object *currentObject = (Object *)objectList->ListGetCurrent();
                if(!currentObject->vertices->ListIsEmpty())
                {
                    glPushMatrix();

                        glEnable(GL_TEXTURE_2D);

                        if(currentObject->ObjectMaterial)
                            glBindTexture( GL_TEXTURE_2D, currentObject->ObjectMaterial->textureGL);
                        else
                            glBindTexture( GL_TEXTURE_2D, 0);

                        //Modify Model position
                        handleMotions(currentObject);
                        handleRotations(currentObject);

                        //Modify Model Matrix
                        glRotatef(currentObject->Angle, currentObject->rotationAxis.elements[0], currentObject->rotationAxis.elements[1], currentObject->rotationAxis.elements[2]);
                        glTranslatef(currentObject->position.elements[0],currentObject->position.elements[1],currentObject->position.elements[2]);
                        glScalef(currentObject->scale.elements[0],currentObject->scale.elements[1],currentObject->scale.elements[2]);

                        //Render Triangles
                        if(!currentObject->triangles->ListIsEmpty())
                            renderTriangles(currentObject);

                        //Render Quads
                        if(!currentObject->squares->ListIsEmpty())
                            renderQuads(currentObject);


                    glPopMatrix();
                    objectList->ListNext();
                }
           }
        }
    }

}



void Scene::handleMotions(Object *currentObject)
{
    if(currentObject->Am || currentObject->V0m)
    {
        vector direction = vector(currentObject->Dm);
        float acc = currentObject->Am;
        if(currentObject->position.elements[1] > -2)
        {
            acc = len( (direction * acc) + vector(0,-10,0) );
            direction = unify( (direction * acc) + vector(0,-10,0) );
        }

        else
        {
            currentObject->position.elements[1] = -2;
        }

        currentObject->V0m +=  currentObject->Am* ((SDL_GetTicks()-currentObject->Tms)/1000);
        double MPF = (double)currentObject->V0m/averageFPS;
        currentObject->position = (currentObject->position) + (direction * MPF);
    }
}

void Scene::handleRotations(Object *currentObject)
{
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
}

int Scene::handleCams(void)
{

    if(!Camlist->ListIsEmpty() && !Camlist->ListIsLast())
    {
        Camera *currentCam = Camlist->ListGetCurrent();
        Camlist->ListNext();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(currentCam->x,currentCam->y,currentCam->width,currentCam->height);
        gluPerspective(currentCam->fov, currentCam->width/currentCam->height, currentCam->nearClip, currentCam->farClip );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(currentCam->position.elements[0],currentCam->position.elements[1],currentCam->position.elements[2],currentCam->lookingDirection.elements[0]+currentCam->position.elements[0],currentCam->lookingDirection.elements[1]+currentCam->position.elements[1],currentCam->lookingDirection.elements[2]+currentCam->position.elements[2],0.0,1.0,0.0);

        return true;
    }

    return false;
}


void Scene::renderQuads(Object *currentObject)
{
    glBegin( GL_QUADS );

            currentObject->squares->ListSetFirst();

            while(!currentObject->squares->ListIsLast())
            {
                struct square *currentSquare = (struct square *)currentObject->squares->ListGetCurrent();

                for(int i=0;i<4;i++)
                {
                    if(currentObject->ObjectMaterial && currentObject->ObjectMaterial->textureGL)
                            glTexCoord2f( currentSquare->texVertex[i]->x, currentSquare->texVertex[i]->y );

                    glVertex3f( currentSquare->objVertex[i]->x, currentSquare->objVertex[i]->y, currentSquare->objVertex[i]->z);
                }

                currentObject->squares->ListNext();
            }

    glEnd();
}

void Scene::renderTriangles(Object *currentObject)
{
    glBegin( GL_TRIANGLES );

            currentObject->triangles->ListSetFirst();

            while(!currentObject->triangles->ListIsLast())
            {

                struct triangle *currentTriangle = (struct triangle *)currentObject->triangles->ListGetCurrent();

                for(int i=0;i<3;i++)
                {
                    if(currentObject->ObjectMaterial && currentObject->ObjectMaterial->textureGL)
                        glTexCoord2f( currentTriangle->texVertex[i]->x, currentTriangle->texVertex[i]->y );

                    glVertex3f( currentTriangle->objVertex[i]->x, currentTriangle->objVertex[i]->y, currentTriangle->objVertex[i]->z);

                }

                currentObject->triangles->ListNext();
            }

    glEnd();
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
