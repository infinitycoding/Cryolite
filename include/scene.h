#ifndef SCENE_H
#define SCENE_H

#include <object.h>
#include <List.h>

class Scene
{
    public:
        Scene(void);
        ~Scene(void);
        void addObject(Object *obj);
        int removeObject(char *name);
        int removeObject(Object *obj);
        void render(void);

        List<Object> *objectList;

        int lasttick;
        int accuracy;
        float averageFPS;

    private:
        void calculateFPS(void);
        void renderQuad(void);
        void handleMotions(Object *currentObject);
        void handleRotations(Object *currentObject);
        int currenttick;
        int ticcount;
        int tickbundle;
        double sum;

};


#endif
