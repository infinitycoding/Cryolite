#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED


#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>

#include <vector.h>
#include <mediaLayer.h>



// put defines here

#define MUSIC_PLAY_PERMANENTLY -1
#define MUSIC_PLAY_ONCE 0

class Music
{
    public:
        struct MusicEntry
        {
            char *name;
            Mix_Music *music;
        };
        List<MusicEntry> musiclist;
        int currentMode;
        MusicEntry *currentMusic;

        bool activ;

        Music();
        Music(const char *musicfile);
        bool addMusic(const char *musicfile);
        bool removeMusic(const char* musicfile);
        bool selectMusic(const char *name, int mode);
        void toggle();

        ~Music();
};


class SoundCache
{
    public:
        struct SoundEntry
        {
            char *name;
            Mix_Chunk *chunk;
            ALuint buffer;
        };


    SoundCache();
    ~SoundCache();

    bool addSound(const char* file);
    bool removeSound(const char *file);
    bool removeSound(ALuint buffer);
    ALuint getSound(const char *file);

    List<SoundEntry> SoundList;
};



class Sound
{

    public:
        struct SoundSettings
        {
            vector direction;
            vector velocity;
            float Gain;
            float MaxGain;
            float MinGain;
            float pitch;
            float refDistance;
            float maxDistance;
            bool loop;
        };

        Sound();
        Sound(SoundSettings *settings);
        Sound(const char *filename, SoundCache *cache);
        Sound(const char *filename, SoundCache *cache,SoundSettings *settings);


        ~Sound();

        bool loadSound(const char *filename);
        bool loadSound(const char *filename, SoundCache *cache);
        void play();
        void stop();
        void pause();
        void resum();
        void toggleLoop();
        void refreshProperties();
        void refreshPosition(vector listener,vector pos);


        ALuint source;
        ALuint buffer;
        SoundSettings *settings;
        SoundCache *cache;

    private:
        void initSound();

};




#endif
