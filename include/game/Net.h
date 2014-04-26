#ifndef NET_H
#define NET_H


#include <scene.h>
#include <SDL_net.h>

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


class Net
{
    public:
        Net(const char *servername, unsigned short serverPort, const char *username);
        void processData(Scene *s);
        int addObject(const char *name, Object *object);
        int deleteObject(const char *name, Object *object);
        int updateObject(const char *name, Object *object);

    private:
        IPaddress serverIP;
        TCPsocket socket;

};


#endif
