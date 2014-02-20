#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <iostream>

#include <sound.h>

using namespace std;


Music::Music()
{
    musiclist = List<MusicEntry>();
    M = ListIterator<MusicEntry>(&musiclist);
    currentMusic = NULL;
    currentMode = -1;
    activ = false;
}

Music::Music(const char *musicfile)
{
    musiclist = List<MusicEntry>();
    M = ListIterator<MusicEntry>(&musiclist);
    currentMode = -1;
    activ = false;

    Mix_Music *mixmusic = Mix_LoadMUS(musicfile);
    if(mixmusic == NULL)
    {
        cerr<<"Could not Load Muisc file:"<<musicfile<<endl;
    }
    else
    {
        currentMusic = new MusicEntry;
        currentMusic->name = new char[strlen(musicfile)+1];
        strcpy(currentMusic->name,musicfile);
        currentMusic->music = mixmusic;
        musiclist.PushFront(currentMusic);
    }
}


bool Music::addMusic(const char *musicfile)
{
    M.SetFirst();
    while(!M.IsLast())
    {
        if(!strncmp(musicfile,M.GetCurrent()->name,strlen(M.GetCurrent()->name)))
        {
            return false;
        }

        M.Next();
    }


    Mix_Music *mixmusic = Mix_LoadMUS(musicfile);
    if(mixmusic == NULL)
    {
        cerr<<"Could not Load Muisc file:"<<musicfile<<endl;
        return false;
    }

    MusicEntry *newMusicEntry = new MusicEntry;
    newMusicEntry->name = new char[strlen(musicfile)+1];
    strcpy(newMusicEntry->name,musicfile);
    newMusicEntry->music = mixmusic;
    musiclist.PushFront(newMusicEntry);
    return true;
}

bool Music::removeMusic(const char* musicfile)
{
    M.SetFirst();
    while(!M.IsLast())
    {
        if(!strncmp(musicfile,M.GetCurrent()->name,strlen(M.GetCurrent()->name)))
        {
            if(M.GetCurrent() == currentMusic)
            {
                Mix_HaltMusic();
                currentMusic = NULL;
                activ = false;
            }
            MusicEntry *entry = M.Remove();
            Mix_FreeMusic(entry->music);
            delete entry->name;
            delete entry;
            return true;
        }

        M.Next();
    }
    return false;
}

bool Music::selectMusic(const char *name, int mode)
{
    M.SetFirst();
    while(!M.IsLast())
    {
        if(!strncmp(name,M.GetCurrent()->name,strlen(M.GetCurrent()->name)))
        {
            currentMode = mode;
            currentMusic = M.GetCurrent();
            Mix_PlayMusic(currentMusic->music, currentMode);
            Mix_PauseMusic();
            activ = false;
            return true;
        }

        M.Next();
    }
    return false;
}

void Music::toggle()
{
    if(activ && currentMusic)
    {
        activ = false;
        Mix_PauseMusic();
    }
    else
    {
        activ = true;
        Mix_ResumeMusic();
    }
}

Music::~Music()
{
    Mix_HaltMusic();
    while(!musiclist.IsEmpty())
    {
        MusicEntry *entry = musiclist.PopFront();
        Mix_FreeMusic(entry->music);
        delete entry;
    }

}


SoundCache::SoundCache()
{
    SoundList = List<SoundEntry>();
}

SoundCache::~SoundCache()
{
    while(!SoundList.IsEmpty())
    {
        SoundEntry *entry = SoundList.PopFront();
        delete entry->name;
        Mix_FreeChunk(entry->chunk);
        delete entry;
    }
}

bool SoundCache::addSound(const char * file)
{
    ListIterator<SoundEntry> i = ListIterator<SoundEntry>(&SoundList);
    i.SetFirst();
    while(!i.IsLast())
    {
        if(!strncmp(file,i.GetCurrent()->name,strlen(i.GetCurrent()->name)))
        {
            return false;
        }

        i.Next();
    }
    Mix_Chunk *sound = Mix_LoadWAV(file);
    if(!sound)
    {
        cerr<< "could not load sound file " << file << endl;
        return false;
    }

    SoundEntry *newEntry = new SoundEntry;
    newEntry->chunk = sound;
    newEntry->buffer = SDL::chunkToBuffer(sound);
    newEntry->name = new char[strlen(file)+1];
    strcpy(newEntry->name,file);
    SoundList.PushFront(newEntry);

    return true;
}

bool SoundCache::removeSound(const char *file)
{
    ListIterator<SoundEntry> i = ListIterator<SoundEntry>(&SoundList);
    i.SetFirst();
    while(!i.IsLast())
    {
        if(!strncmp(file,i.GetCurrent()->name,strlen(i.GetCurrent()->name)))
        {
            SoundEntry *entry = i.Remove();
            delete entry->name;
            Mix_FreeChunk(entry->chunk);
            delete entry;
            return true;
        }

        i.Next();
    }
    cerr<<file<<" does not exist in this Soundcache"<<endl;
    return false;
}

bool SoundCache::removeSound(ALuint buffer)
{
    ListIterator<SoundEntry> i = ListIterator<SoundEntry>(&SoundList);
    i.SetFirst();
    while(!i.IsLast())
    {
        if(i.GetCurrent()->buffer == buffer)
        {
            SoundEntry *entry = i.Remove();
            delete entry->name;
            Mix_FreeChunk(entry->chunk);
            delete entry;
            return true;
        }

        i.Next();
    }
    cerr<<"sound "<<buffer<<" does not exist in this Soundcache"<<endl;
    return false;
}


ALuint SoundCache::getSound(const char *file)
{
    ListIterator<SoundEntry> i = ListIterator<SoundEntry>(&SoundList);
    i.SetFirst();
    while(!i.IsLast())
    {
        if(!strncmp(file,i.GetCurrent()->name,strlen(i.GetCurrent()->name)))
        {
            return i.GetCurrent()->buffer;
        }

        i.Next();
    }

    cerr<<file<<" does not exist in this Soundcache return NULL Buffer"<<endl;
    return 0;
}


Sound::Sound()
{
    initSound();
}

Sound::Sound(SoundSettings *settings)
{
    source = 0;
    buffer = 0;
    this->cache = NULL;
    this->settings = settings;
}

Sound::Sound(const char *filename, SoundCache *cache)
{
    initSound();
    this->cache = cache;
    cache->addSound(filename);
    buffer = cache->getSound(filename);
    if(buffer)
    {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        cerr<<"Sound loaded"<<endl;
    }
}



Sound::Sound(const char *filename, SoundCache *cache, SoundSettings *settings)
{
    source = 0;
    buffer = 0;
    this->cache = cache;
    this->settings = settings;
    cache->addSound(filename);
    buffer = cache->getSound(filename);
    if(buffer)
    {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        cerr<<"Sound loaded"<<endl;
    }
}

Sound::~Sound()
{
    int sourceState = 0;
    alGetSourcei(source,AL_SOURCE_STATE, &sourceState);
    if( sourceState == AL_PLAYING || sourceState == AL_PAUSED)
        alSourcei(source,AL_SOURCE_STATE, AL_STOPPED);

    if(source)
        alDeleteSources(1,&source);

    delete settings;
}


bool Sound::loadSound(const char *filename)
{
    if(!cache)
    {
        cerr<<"Sound: Cache was not registert"<<endl;
        return false;
    }

    cache->addSound(filename);
    buffer = cache->getSound(filename);
    if(buffer)
    {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
    }

    return true;
}

bool Sound::loadSound(const char *filename,SoundCache *cache)
{
    if(!cache)
    {
        cerr<<"Sound: Cache was not registert"<<endl;
        return false;
    }
    this->cache = cache;

    cache->addSound(filename);
    buffer = cache->getSound(filename);
    if(buffer)
    {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
    }

    return true;
}


void Sound::play()
{
    if(source && buffer)
    {
        alSourcePlay(source);
        return;
    }

    cerr<<"No Sound is loaded for current Object"<<endl;

}

void Sound::stop()
{
    alSourcei(source,AL_SOURCE_STATE, AL_STOPPED);
}

void Sound::pause()
{
    alSourcei(source,AL_SOURCE_STATE, AL_PAUSED);
}

void Sound::resum()
{
    alSourcei(source,AL_SOURCE_STATE, AL_PLAYING);
}

void Sound::toggleLoop()
{
    int sourceState = 0;
    alGetSourcei(source,AL_LOOPING, &sourceState);
    sourceState = !sourceState;
    settings->loop = sourceState;
    if(sourceState && source && buffer)
        alSourcePlay(source);

    alSourcei(source,AL_LOOPING, sourceState);
}


void Sound::refreshPosition(vector listener, vector pos)
{
    vector currenPosition;
    currenPosition = listener-pos;
    alSource3f(source, AL_POSITION, currenPosition.x, currenPosition.y, currenPosition.z);
}


void Sound::initSound()
{
    source = 0;
    buffer = 0;
    settings = new SoundSettings;
    settings->direction = vector(0,0,0);
    settings->velocity = vector(0,0,0);
    settings->Gain = 1;
    settings->MaxGain = 1;
    settings->MinGain = 0;
    settings->pitch = 1;
    settings->refDistance = 0;
    settings->loop = false;
    settings->maxDistance = 50;
    cache = NULL;
}

void Sound::refreshProperties()
{
    alSource3f(source, AL_DIRECTION, settings->direction.x, settings->direction.y, settings->direction.z);
    alSource3f(source, AL_VELOCITY, settings->velocity.x, settings->velocity.y, settings->velocity.z);

    alSourcef(source, AL_GAIN , settings->Gain);
    alSourcef(source, AL_MAX_GAIN, settings->MaxGain);
    alSourcef(source, AL_MIN_GAIN, settings->MinGain);
    alSourcef(source, AL_PITCH, settings->pitch);
    alSourcef(source, AL_REFERENCE_DISTANCE, settings->refDistance);
    alSourcef(source, AL_MAX_DISTANCE, settings->maxDistance);
    if(settings->loop)
        alSourcei(source, AL_LOOPING, AL_TRUE);
    else
        alSourcei(source, AL_LOOPING, AL_FALSE);
}
