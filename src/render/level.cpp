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
    actualBackgroundMusic = NULL;
    backgroundMusics = new List<struct locationMusic>;
}


bool Level::loadLevelFile(const char *filename)
{
    return false;
}


bool Level::vectorInCube(vector v, struct cube c)
{
    return ((v.x >= c.startPos.x && v.x <= c.endPos.x) && (v.y >= c.startPos.y && v.y <= c.endPos.y) && (v.z >= c.startPos.z && v.z <= c.endPos.z));
}


struct locationMusic *Level::addBackgroundMusic(struct locationMusic *newBackgroundMusic)
{
    backgroundMusics->PushFront(newBackgroundMusic);
    return newBackgroundMusic;
}


bool Level::refreshBackgroundMusic(vector playerPos)
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

    return false;
}


void Level::testMusic()
{
    bgmusic->addMusic(SOUND(moon.mp3));
    struct locationMusic *moon = new struct locationMusic;
    strncpy(moon->musicname, SOUND(moon.mp3), 40);
    moon->location.startPos = vector(-50, -10, -50);
    moon->location.endPos = vector(0, 10, 0);
    addBackgroundMusic(moon);

    /*bgmusic->addMusic(SOUND(majestic-theme.wav));
    struct locationMusic *majestic = new struct locationMusic;
    strncpy(majestic->musicname, SOUND(majestic-theme.wav), 40);
    majestic->location.startPos = vector(0, -10, 0);
    majestic->location.endPos = vector(50, 10, 50);
    addBackgroundMusic(majestic);*/
}
