#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED



#include <vector.h>
#include <sound.h>
#include <List.h>



struct cube
{
    vector startPos;
    vector endPos;
};

struct locationMusic
{
    struct cube location;
    Music *music;
};


class Level
{
    public:
        Level();
        Level(const char *filename);
        ~Level();

        void initLevel();
        bool loadLevelFile(const char *filename);

        bool vectorInCube(vector v, struct cube c);

        struct locationMusic *addBackgroundMusic(struct locationMusic *newBackgroundMusic);
        bool refreshBackgroundMusic(vector playerPos);

    protected:
        struct locationMusic *actualBackgroundMusic;
        List<struct locationMusic> *backgroundMusics;
};



#endif
