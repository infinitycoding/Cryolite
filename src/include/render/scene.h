#ifndef SCENE_H
#define SCENE_H

#include <object.h>
#include <camera.h>
#include <List.h>
#include <light.h>
#include <physics/PhysicsEngine.h>
#include <fps.h>



class Scene
{
    public:

        Scene(void);
        ~Scene(void);

        void addObject(Object *obj);
        int removeObject(Object *obj);
        void addCam(Camera *cam);
        int removeCam(Camera *cam);
        void addLamp(Lamp *L);
        int removeLamp(Lamp *L);

        void render(void);
        int handleCams(ListIterator<Camera> *c);

        FPS *fps;

        List<Object> *objectList;
        List<Camera> *Camlist;
        List<Lamp> *globalLamps;

        bool currentScene;
        GlobalLight *GlobalAmbience;

        vector listenerPosition;



    private:
        void renderPolygones(Object *currentObject);
        void resetLights(void);

        LightManager *LM;
};


#endif
