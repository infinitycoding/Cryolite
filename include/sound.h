#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED


#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>


// put defines here

#define MUSIC_PLAY_PERMANENTLY -1
#define MUSIC_PLAY_ONCE 0

class Music
{
    public:
        Mix_Music *music;
        bool activ;

        Music();
        Music(const char *musicfile, int mode);
        Music(const char *musicfile, int mode,bool play);
        ~Music();
        void toggle();

    private:

        int mode;

};


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
