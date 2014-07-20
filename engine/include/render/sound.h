#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED
/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <mediaLayer.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <SDL_mixer.h>

#include <util/vector.h>




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
