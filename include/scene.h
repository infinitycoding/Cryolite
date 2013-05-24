#ifndef SCENE_H
#define SCENE_H
#include "object.h"
#include "list.h"

class Scene
{
    public:
        Scene(void);
        ~Scene(void);
        void addObject(Object *obj);
        int removeObject(char *name);
        int removeObject(Object *obj);
        void render(void);

        struct List *objectList;

        int lasttick;
        int accuracy;
        float averageFPS;

    private:
        void calculateFPS(void);
        int currenttick;
        int ticcount;
        int tickbundle;
        double sum;

};


#endif
