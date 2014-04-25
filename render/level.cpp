#include <level.h>



using namespace std;



Level::Level()
{
    initLevel();
}


Level::Level(const char *filename)
{
    initLevel();

    loadLevelFile(filename);
}


Level::~Level()
{
    delete backgroundMusics;
}


void Level::initLevel()
{
    bgmusic = new Music();
    bgmusicActivated = true;
    actualBackgroundMusic = NULL;
    backgroundMusics = new List<struct locationMusic>;

    testMusic();
}


bool Level::loadLevelFile(const char *filename)
{
    return false;
}


bool Level::vectorInCube(vector v, struct cube c)
{
    return ((v.x[0] >= c.startPos.x[0] && v.x[0] <= c.endPos.x[0]) && (v.x[1] >= c.startPos.x[1] && v.x[1] <= c.endPos.x[1]) && (v.x[2] >= c.startPos.x[2] && v.x[2] <= c.endPos.x[2]));
}


struct locationMusic *Level::addBackgroundMusic(struct locationMusic *newBackgroundMusic)
{
    backgroundMusics->PushFront(newBackgroundMusic);
    return newBackgroundMusic;
}


bool Level::refreshBackgroundMusic(vector playerPos)
{
    if(bgmusicActivated)
    {
        if(actualBackgroundMusic != NULL && vectorInCube(playerPos, actualBackgroundMusic->location))
            return false;

        if(backgroundMusics->IsEmpty())
            return false;

        ListIterator<locationMusic> i = ListIterator<locationMusic>(backgroundMusics);
        i.SetFirst();

        do
        {
            if(vectorInCube(playerPos, i.GetCurrent()->location))
            {
                actualBackgroundMusic = i.GetCurrent();
                bgmusic->selectMusic(actualBackgroundMusic->musicname, -1);
                bgmusic->toggle();
                return true;
            }

            i.Next();
        }while(!i.IsLast());

        if(actualBackgroundMusic != NULL)
                bgmusic->toggle();

        actualBackgroundMusic = NULL;
    }

    return false;
}


void Level::activateBackgroundMusic()
{
    bgmusicActivated = true;
}


void Level::deactivateBackgroundMusic()
{
    bgmusicActivated = false;

    if(actualBackgroundMusic != NULL)
            bgmusic->toggle();

    actualBackgroundMusic = NULL;
}


void Level::toggleBackgroundMusic()
{
    if(bgmusicActivated)
        deactivateBackgroundMusic();
    else
        activateBackgroundMusic();
}


void Level::testMusic()
{
    bgmusic->addMusic(SOUND(moon.mp3));
    struct locationMusic *moon = new struct locationMusic;
    strncpy(moon->musicname, SOUND(moon.mp3), 40);
    moon->location.startPos = vector(-50.0, -10.0, -50.0);
    moon->location.endPos = vector(0.0, 10.0, 50.0);
    addBackgroundMusic(moon);

    bgmusic->addMusic(SOUND(majestic-theme.wav));
    struct locationMusic *majestic = new struct locationMusic;
    strncpy(majestic->musicname, SOUND(majestic-theme.wav), 40);
    majestic->location.startPos = vector(0.0, -10.0, -50.0);
    majestic->location.endPos = vector(50.0, 10.0, 50.0);
    addBackgroundMusic(majestic);
}
