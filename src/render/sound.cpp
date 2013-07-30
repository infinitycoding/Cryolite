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




// todo: flag toggle after finishing playloops via global music manager



Sound::Sound()
{
    initSound();
}


Sound::Sound(const char *filename)
{
    initSound();

    loadSoundFile(filename);
}


Sound::~Sound()
{

}


bool Sound::loadSoundFile(const char *filename)
{
    return true;
}


bool Sound::playSound(struct soundSettings *settings)
{
    return true;
}


void Sound::initSound()
{

}
