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
        void render(void);

        struct List *objectList;
};


#endif
