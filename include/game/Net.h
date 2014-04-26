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
    connSignal s;
    int id;
    vector position;
    char *objtype;
};

struct deleteObjectPackage
{
    connSignal s;
    int id;
};




class Net
{
    public:
        Net(const char *servername, unsigned short serverPort, const char *username);
        void updateScene(Scene *s);
        int addObject(Object *object);
        int deleteObject(Object *object);
        int updateObject(Object *object);

    private:
        IPaddress serverIP;
        TCPsocket socket;

};


#endif
