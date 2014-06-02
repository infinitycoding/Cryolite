#ifndef NET_H
#define NET_H


#include <scene.h>
#include <SDL_net.h>
#include <object.h>

typedef enum
{
    NOSIGNAL = 0,
    ADDOBJECT = 1,
    REMOVEOBJECT = 2,
    UPDATEOBJECT = 3,
    OK = 4,
    UPDATEID = 5,
    SERVER = 0xc0ffee,
    USER = 0xb0b,
}connSignal;

struct loginPackage
{
    connSignal s;
    char name[20];
};

struct addObjectPackage
{
    int id;
    vector position;
    vector impulse;
    char objtype[20];
    char filename[100];
};

struct updateObjectPackage
{
    int id;
    vector position;
    vector impulse;
};

struct deleteObjectPackage
{
    int id;
};

struct updateIDPackage
{
    unsigned int newID;
};




class Net
{
    public:
        Net(const char *servername, unsigned short serverPort, const char *username);
        ~Net();
        void updateScene(Scene *s);

        int addObject(Object *object);
        int deleteObject(Object *object);
        int updateObject(Object *object);

    private:
        unsigned int highestID;
        IPaddress serverIP;
        TCPsocket socket;
        SDLNet_SocketSet sset;

};


#endif
