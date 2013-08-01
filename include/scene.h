#ifndef SCENE_H
#define SCENE_H

#include <object.h>
#include <camera.h>
#include <List.h>
#include <light.h>
#include <vector.h>


struct Collision
{
    Object *object1;
    Object *object2;
    vector position;
};

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

        List<Object> *objectList;
        List<Camera> *Camlist;
        List<Lamp> *globalLamps;
        List<Collision> *collisions;

        bool currentScene;
        GlobalLight *GlobalAmbience;


        int lasttick;
        int accuracy;
        float averageFPS;

        vector listenerPosition;



    private:
        void calculateFPS(void);
        void renderPolygones(Object *currentObject);
        void interpolatePhysics(Object *currentObject);
        void resetLights(void);
        void calculateCollisions(void);
        bool approximation(Object *obj1, Object *obj2);
        Collision *collision(Object *obj1, Object *obj2);

        LightManager *LM;
        int currenttick;
        int ticcount;
        int tickbundle;
        double sum;

};


#endif
