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


        // Background Music
        bool vectorInCube(vector v, struct cube c);

        struct locationMusic *addBackgroundMusic(struct locationMusic *newBackgroundMusic);
        bool refreshBackgroundMusic(vector playerPos);
        void activateBackgroundMusic();
        void deactivateBackgroundMusic();
        void toggleBackgroundMusic();

        void testMusic(); //only to debug


        // TODO: write script integration


        // TODO: write object integration


        // TODO: write chunk system


        // TODO: write groundmap system


    protected:
        Music *bgmusic;
        bool bgmusicActivated;
        struct locationMusic *actualBackgroundMusic;
        List<struct locationMusic> *backgroundMusics;
};



#endif
