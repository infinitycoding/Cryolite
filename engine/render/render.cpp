#include <render.h>



void Render::render(Viewport *view)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(view->lvl->GlobalAmbience && !view->lvl->currentScene)
        view->lvl->GlobalAmbience->activateLight();

    if(!view->lvl->globalLamps->IsEmpty() && !view->lvl->currentScene)
        resetLights(view);

    else if(!view->lvl->GlobalAmbience && view->lvl->globalLamps->IsEmpty())
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


    view->lvl->fps->calculate();

    // Interpolate Physics
    Object *currentObject = NULL;
    ListIterator<Object> O = *ListIterator<Object>(view->lvl->objectList).SetFirst();

    while(!O.IsLast())
    {
        currentObject = O.GetCurrent();
        currentObject->physObj->interpolatePhysics(&(currentObject->localPosition), view->lvl->fps->get());
        O.Next();
    }

    view->lvl->collisions->checkCollisions();

    // Debug only

    List<collision> *collList = view->lvl->collisions->getCollisions();
    ListIterator<collision> collIterator = *ListIterator<collision>(collList).SetFirst();
    collision *currentCollision = NULL;
    vector temp;

    while(!collIterator.IsLast())
    {
        currentCollision = collIterator.GetCurrent();

        if(!strncmp(currentCollision->obj1->objType->objectTypeName, "projectile", strlen("projectile")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with projectile %p!\n", currentCollision->obj1, currentCollision->obj2);
            view->lvl->removeObject(currentCollision->obj1);
            view->lvl->removeObject(currentCollision->obj2);
            delete currentCollision->obj1;
            delete currentCollision->obj2;
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "projectile", strlen("projectile")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "ground", strlen("ground")))
        {
            printf("Projectile %p collided with ground!\n", currentCollision->obj1);
            view->lvl->removeObject(currentCollision->obj1);
            delete currentCollision->obj1;
        }
        else if(!strncmp(currentCollision->obj1->objType->objectTypeName, "ground", strlen("ground")) && !strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with ground!\n", currentCollision->obj2);
            view->lvl->removeObject(currentCollision->obj2);
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
            view->lvl->removeObject(currentCollision->obj1);
            delete currentCollision->obj1;
        }
        else if(!strncmp(currentCollision->obj2->objType->objectTypeName, "projectile", strlen("projectile")))
        {
            printf("Projectile %p collided with object %p!\n", currentCollision->obj2, currentCollision->obj1);
            currentCollision->obj1->physObj->setImpulse(currentCollision->obj1->physObj->getImpulse() + currentCollision->obj2->physObj->getImpulse());
            view->lvl->removeObject(currentCollision->obj2);
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

    view->lvl->collisions->checkCollisions();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(view->x,view->y,view->width,view->height);
    gluPerspective(view->cam->fov, view->width/view->height, view->cam->nearClip, view->cam->farClip );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(view->cam->getPosition().x[0],view->cam->getPosition().x[1],view->cam->getPosition().x[2],view->cam->lookingDirection.x[0]+view->cam->getPosition().x[0],view->cam->lookingDirection.x[1]+view->cam->getPosition().x[1],view->cam->lookingDirection.x[2]+view->cam->getPosition().x[2],0.0,1.0,0.0);

    if(!view->lvl->globalLamps->IsEmpty())
    {
        ListIterator<Lamp> L(view->lvl->globalLamps);
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

    if(!view->lvl->objectList->IsEmpty())
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

float shine[] { 0.75f, 0.75f, 0.75f, 1 };

void Render::renderPolygones(Object *currentObject)
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



void Render::resetLights(Viewport *view)
{
    ListIterator<Lamp> L = *ListIterator<Lamp>(view->lvl->globalLamps).SetFirst();
    while(!L.IsLast())
    {
        if(L.GetCurrent()->activ)
            L.GetCurrent()->refresh();
        L.Next();
    }
}
