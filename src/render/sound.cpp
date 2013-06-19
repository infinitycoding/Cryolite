#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>


#include <sound.h>



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
