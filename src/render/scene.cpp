#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <SDL.h>
#include <general_def.h>
#include <scene.h>
#include <object.h>


Scene::Scene()
{
    objectList = new List<Object>;
    Camlist = new List<Camera>;
    globalLamps = new List<Lamp>;
    CL = new CollisionLocate(objectList);
    LM = new LightManager();
    GlobalAmbience = NULL;
    listenerPosition = vector(0,0,0);

}

Scene::~Scene()
{
    delete objectList;
    delete Camlist;
    delete globalLamps;
    delete CL;
    delete LM;
}


void Scene::addObject(Object *obj)
{
    this->objectList->PushFront(obj);
}

int Scene::removeObject(Object *obj)
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

void Scene::addCam(Camera *cam)
{
    Camlist->PushFront(cam);
}

int Scene::removeCam(Camera *cam)
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

void Scene::addLamp(Lamp *L)
{
    globalLamps->PushFront(L);
    L->Lightnum = LM->getLightNum();
    L->reg = true;
    L->refresh();
}

int Scene::removeLamp(Lamp *L)
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

extern FPS *fps;

void Scene::render()
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
        currentObject->physObj.interpolatePhysics(&currentObject->localPosition, fps->get());
        O.Next();
    }

    ListIterator<Camera> c = *ListIterator<Camera>(Camlist).SetFirst();
    while(handleCams(&c))
    {
        if(!globalLamps->IsEmpty())
        {
            ListIterator<Lamp> L = *ListIterator<Lamp>(globalLamps).SetFirst();
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
                }

                if(!currentObject->sounds->IsEmpty())
                {
                    ListIterator<Sound> S = *ListIterator<Sound>(currentObject->sounds).SetFirst();
                    while(!S.IsLast())
                    {
                        S.GetCurrent()->refreshPosition(listenerPosition,currentObject->getPosition());
                        S.Next();
                    }
                }

                O.Next();
           }
        }

    }

    currentScene = true;
    CL->calculateCollisions();
}

void Scene::resetLights(void)
{
    ListIterator<Lamp> L = *ListIterator<Lamp>(globalLamps).SetFirst();
    while(!L.IsLast())
    {
        if(L.GetCurrent()->activ)
            L.GetCurrent()->refresh();
        L.Next();
    }
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
        glBegin( GL_POLYGON );

            glMaterialfv(GL_AMBIENT, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->ambiantMatColor);
            glMaterialfv(GL_DIFFUSE, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->diffuseMatColor);
            glMaterialfv(GL_SPECULAR, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->specularMatColor);
            glMaterialfv(GL_EMISSION, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->emissiveMatColor);
            glMaterialf(GL_SHININESS, GL_FRONT_AND_BACK,currentObject->objType->ObjectTypeMaterial->specularExponent);


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
