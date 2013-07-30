#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED



#include <vector.h>
#include <sound.h>
#include <List.h>
#include <general_def.h>



struct cube
{
    vector startPos;
    vector endPos;
};

struct locationMusic
{
    struct cube location;
    char musicname[40];
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

        void testMusic(); //only to debug

    protected:
        Music *bgmusic;
        struct locationMusic *actualBackgroundMusic;
        List<struct locationMusic> *backgroundMusics;
};



#endif
