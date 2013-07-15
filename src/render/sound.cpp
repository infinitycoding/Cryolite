#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>


#include <sound.h>


Music::Music()
{
    music = NULL;
    activ = false;
}

Music::Music(const char *musicfile, int mode)
{
    music = Mix_LoadMUS(musicfile);
    if(music == NULL)
    {
        fprintf(stderr,"Could not Load Muisc file: %s \n", musicfile);
    }
    else
    {
        Mix_PlayMusic( music, mode );
        Mix_PauseMusic();
    }
    activ = false;
}

Music::Music(const char *musicfile, int mode, bool play)
{
    music = Mix_LoadMUS(musicfile);
    if(music == NULL)
    {
        fprintf(stderr,"Could not Load Muisc file: %s \n", musicfile);
        activ = false;
    }
    else
    {
        this->mode = mode;
        Mix_PlayMusic( music, mode );
        activ = play;
        if(!play)
        {
            Mix_PauseMusic();
        }
    }
}

Music::~Music()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
}

void Music::toggle()
{
    if(activ)
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
