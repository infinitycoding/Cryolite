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
    this->GlobalAmbience = NULL;
    currenttick = 0;
    ticcount = 0;
    tickbundle = 3;
    sum = 0;
    lasttick = SDL_GetTicks();
    accuracy = 60;
    averageFPS = 60;

}

Scene::~Scene()
{
    delete this->objectList;
}


void Scene::addObject(Object *obj)
{
    this->objectList->PushFront(obj);
}

int Scene::removeObject(Object *obj)
{
    int delObj = 0;
    ListIterator<Object> i = ListIterator<Object>(objectList);
    i.SetFirst();
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


void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(GlobalAmbience && !currentScene)
        GlobalAmbience->activateLight();

    else if(!GlobalAmbience)
    {
        GLboolean activlight;
        glGetBooleanv(GL_LIGHTING, &activlight);
        if(activlight)
            glDisable(GL_LIGHTING);
    }


    calculateFPS();

    // Interpolate Physics
    ListIterator<Object> O = *ListIterator<Object>(objectList).SetFirst();
    while(!O.IsLast())
    {
        interpolatePhysics(O.GetCurrent());
        O.Next();
    }


    ListIterator<Camera> c = *ListIterator<Camera>(Camlist).SetFirst();
    while(handleCams(&c))
    {
        if(!objectList->IsEmpty())
        {
            glMatrixMode(GL_MODELVIEW);

            O.SetFirst();
            while(!O.IsLast())
            {
                Object *currentObject = O.GetCurrent();
                if(!currentObject->objType->vertices->IsEmpty())
                {
                    glPushMatrix();

                        glEnable(GL_TEXTURE_2D);

                        if(currentObject->objType->ObjectTypeMaterial)
                            glBindTexture( GL_TEXTURE_2D, currentObject->objType->ObjectTypeMaterial->ambiantTexture->nr);
                        else
                            glBindTexture( GL_TEXTURE_2D, 0);


                        //Modify Model Matrix
                        glRotatef(currentObject->Angle, currentObject->rotationAxis.x, currentObject->rotationAxis.y, currentObject->rotationAxis.z);
                        glTranslatef(currentObject->getPosition().x,currentObject->getPosition().y,currentObject->getPosition().z);
                        glScalef(currentObject->scale.x,currentObject->scale.y,currentObject->scale.z);

                        //Render Polyganes
                        if(!currentObject->objType->polygones->IsEmpty())
                            renderPolygones(currentObject);


                    glPopMatrix();
                }

                O.Next();
           }
        }
    }

}



void Scene::interpolatePhysics(Object *currentObject)
{

}


int Scene::handleCams(ListIterator<Camera> *c)
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
        gluLookAt(currentCam->getPosition().x,currentCam->getPosition().y,currentCam->getPosition().z,currentCam->lookingDirection.x+currentCam->getPosition().x,currentCam->lookingDirection.y+currentCam->getPosition().y,currentCam->lookingDirection.z+currentCam->getPosition().z,0.0,1.0,0.0);

        return true;
    }

    return false;
}


void Scene::renderPolygones(Object *currentObject)
{

    ListIterator<Polygon> p = ListIterator<Polygon>(currentObject->objType->polygones);
    p.SetFirst();

    while(!p.IsLast())
    {
        Polygon *currentPolygon = (Polygon *)p.GetCurrent();

        glMaterialfv(GL_AMBIENT, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->ambiantMatColor);
        glMaterialfv(GL_DIFFUSE, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->diffuseMatColor);
        glMaterialfv(GL_SPECULAR, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->specularMatColor);
        glMaterialfv(GL_EMISSION, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->emissiveMatColor);

        glBegin( GL_POLYGON );

            for(int i=0;i < currentPolygon->getVertexAmount();i++)
            {
                if(currentPolygon->getNormVector(i) != NULL)
                    glNormal3f(currentPolygon->getNormVector(i)->x,currentPolygon->getNormVector(i)->y,currentPolygon->getNormVector(i)->z);

                if(currentObject->objType->ObjectTypeMaterial && currentObject->objType->ObjectTypeMaterial->ambiantTexture && currentPolygon->getTexVertex(i) != NULL)
                        glTexCoord2f( currentPolygon->getTexVertex(i)->getX(), currentPolygon->getTexVertex(i)->getY() );

                if(currentPolygon->getObjVertex(i) != NULL)
                    glVertex3f( currentPolygon->getObjVertex(i)->getX(), currentPolygon->getObjVertex(i)->getY(), currentPolygon->getObjVertex(i)->getZ());
            }

        glEnd();

        p.Next();
    }
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
