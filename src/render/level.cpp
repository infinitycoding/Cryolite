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

         if(actualBackgroundMusic != NULL)
                actualBackgroundMusic->music->toggle();

            actualBackgroundMusic = i.GetCurrent();
            actualBackgroundMusic->music->toggle();
            return true;
        }

        i.Next();
    }while(!i.IsLast());

    if(actualBackgroundMusic != NULL)
            actualBackgroundMusic->music->toggle();

    actualBackgroundMusic = NULL;

    return false;
}
