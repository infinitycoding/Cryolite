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
    backgroundMusics->ListPushFront(newBackgroundMusic);
    return newBackgroundMusic;
}


bool Level::refreshBackgroundMusic(vector playerPos)
{
    if(actualBackgroundMusic != NULL && vectorInCube(playerPos, actualBackgroundMusic->location))
        return false;

    if(backgroundMusics->ListIsEmpty())
        return false;

    backgroundMusics->ListSetFirst();

    do
    {

        if(vectorInCube(playerPos, backgroundMusics->ListGetCurrent()->location))
        {

         if(actualBackgroundMusic != NULL)
                actualBackgroundMusic->music->toggle();

            actualBackgroundMusic = backgroundMusics->ListGetCurrent();
            actualBackgroundMusic->music->toggle();
            return true;
        }

        backgroundMusics->ListNext();
    }while(!backgroundMusics->ListIsLast());

    if(actualBackgroundMusic != NULL)
            actualBackgroundMusic->music->toggle();

    actualBackgroundMusic = NULL;

    return false;
}
