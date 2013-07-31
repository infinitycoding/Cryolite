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
        currentMusic->name = (char*)musicfile;
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
    newMusicEntry->name = (char*)musicfile;
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
            Mix_PlayMusic( currentMusic->music, currentMode );
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

bool SoundCache::addSound(char * file)
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
    newEntry->buffer = SDL::chuckToBuffer(sound);
    newEntry->name = new char[strlen(file)+1];
    strcpy(newEntry->name,file);
    SoundList.PushFront(newEntry);

    return true;
}

bool SoundCache::removeSound(char *file)
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


ALuint SoundCache::getSound(char *file)
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
