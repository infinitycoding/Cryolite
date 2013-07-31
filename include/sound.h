#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED


#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>

#include <List.h>
#include <object.h>
#include <vector.h>
#include <sdl.h>



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
        ListIterator<MusicEntry> M;
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

    bool addSound(char * file);
    bool removeSound(char *file);
    bool removeSound(ALuint buffer);
    ALuint getSound(char *file);

    List<SoundEntry> SoundList;
};



class Sound
{

    public:
        struct SoundSettings
        {
            vector relation;
            Object *relativObject;
            vector direction;
            vector velocity;
            float Gain;
            float MaxGain;
            float MinGain;
            float pitch;
            float refDistance;
            int times;
            bool loop;
        };

        Sound();
        Sound(char *filename, SoundCache *cache);
        Sound(Object *relativObject);
        Sound(Object *relativObject,vector relation);
        Sound(Object *relativObject,vector relation, char *filename, SoundCache *cache);

        ~Sound();

        bool loadSound(char *filename);
        bool loadSound(char *filename, SoundCache *cache);
        bool playSound();
        void refreshpProperties();
        void refreshpPosition();


        ALuint source;
        ALuint buffer;
        SoundSettings *settings;
        SoundCache *cache;

    private:
        void initSound();

};




#endif
