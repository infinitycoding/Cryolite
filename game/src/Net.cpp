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
}


void Net::updateScene(Scene *s)
{

}


int Net::addObject(Object *object)
{
    struct addObjectPackage newobj;

    object->ID = highestID++;

    newobj.s = ADDOBJECT;
    newobj.id = object->ID;
    newobj.position = object->localPosition;
    strncpy(newobj.objtype, object->objType->objectTypeName, 20);

    return SDLNet_TCP_Send(socket, &newobj, sizeof(struct addObjectPackage));
}


int Net::deleteObject(Object *object)
{
    struct deleteObjectPackage delobj;

    delobj.s = REMOVEOBJECT;
    delobj.id = object->ID;

    return SDLNet_TCP_Send(socket, &delobj, sizeof(struct deleteObjectPackage));
}


int Net::updateObject(Object *object)
{

}
