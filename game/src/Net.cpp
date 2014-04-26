#include <cstring>
#include <Net.h>


Net::Net(const char *servername, unsigned short serverPort, const char *username)
{
    highestID = 0;

    SDLNet_ResolveHost(&serverIP,servername,serverPort);
    socket = SDLNet_TCP_Open(&serverIP);
    if(!socket)
    {
        printf("could not connect to server\n");
        exit(-1);
    }

    struct loginPackage login;
    login.s = USER;
    strncpy(login.name,username,20);
    if(SDLNet_TCP_Send(socket, &login, sizeof(loginPackage)) != sizeof(loginPackage))
    {
        printf("could not send data to server\n");
        exit(-1);
    }

    connSignal response = NOSIGNAL;
    if(SDLNet_TCP_Recv(socket, &response, sizeof(connSignal))!= sizeof(connSignal))
    {
        printf("no response from server\n");
        exit(-1);
    }

    if(response != SERVER)
    {
        printf("the ip does not refer to a game server\n");
        exit(-1);
    }

    response = NOSIGNAL;
    if(SDLNet_TCP_Recv(socket, &response, sizeof(connSignal))!= sizeof(connSignal))
    {
        printf("no response from server\n");
        exit(-1);
    }

    if(response != OK)
    {
        printf("the server does not accept your login data\n");
        exit(-1);
    }

    sset = SDLNet_AllocSocketSet(1);

    if(SDLNet_TCP_AddSocket(sset, socket) == -1)
    {
        printf("Unable to add socket to sockset\n");
        exit(-1);
    }
}


Net::~Net()
{
    SDLNet_FreeSocketSet(sset);
}


void Net::updateScene(Scene *s)
{
    if(SDLNet_CheckSockets(sset, 10) == 0)
        return;

    if(SDLNet_SocketReady(socket) == 1)
    {
        printf("connection to server lost\n");

        exit(-1);
    }
}


int Net::addObject(Object *object)
{
    connSignal s = ADDOBJECT;
    struct addObjectPackage newobj;

    object->ID = highestID++;

    newobj.id = object->ID;
    newobj.position = object->localPosition;
    newobj.impulse = object->physObj->getImpulse();
    strncpy(newobj.objtype, object->objType->objectTypeName, 20);

    SDLNet_TCP_Send(socket, &s, sizeof(connSignal));
    return SDLNet_TCP_Send(socket, &newobj, sizeof(struct addObjectPackage));
}


int Net::deleteObject(Object *object)
{
    connSignal s = REMOVEOBJECT;
    struct deleteObjectPackage delobj;

    delobj.id = object->ID;

    SDLNet_TCP_Send(socket, &s, sizeof(connSignal));
    return SDLNet_TCP_Send(socket, &delobj, sizeof(struct deleteObjectPackage));
}


int Net::updateObject(Object *object)
{

}
