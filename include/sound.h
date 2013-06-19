#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED




#include <AL/alut.h>


// put defines here



struct soundSettings
{

};


class Sound
{

    public:

        Sound();
        Sound(const char *filename);
        ~Sound();

        bool loadSoundFile(const char *filename);
        bool playSound(struct soundSettings *settings);

    private:

        void initSound();




};




#endif
