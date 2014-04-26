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

    if(SDLNet_SocketReady(socket))
    {
        connSignal sig;

        struct deleteObjectPackage del;
        struct addObjectPackage add;
        struct updateObjectPackage upd;

        Object *currentObject;
        ListIterator<Object> O;

        SDLNet_TCP_Recv(socket, &sig, sizeof(connSignal));

        switch(sig)
        {
            case NOSIGNAL:
            break;

            case ADDOBJECT:
                SDLNet_TCP_Recv(socket, &add, sizeof(addObjectPackage));

                currentObject = new Object(add.filename, add.objtype);
                currentObject->localPosition = add.position;
                currentObject->physObj->setImpulse(add.impulse);
                currentObject->ID = add.id;
                highestID = add.id + 1;

                s->addObject(currentObject);
            break;

            case REMOVEOBJECT:
                SDLNet_TCP_Recv(socket, &del, sizeof(deleteObjectPackage));

                currentObject = NULL;
                O = *ListIterator<Object>(s->objectList).SetFirst();

                while(!O.IsLast())
                {
                    currentObject = O.GetCurrent();

                    if(currentObject->ID == del.id)
                    {
                        s->removeObject(currentObject);
                        delete currentObject;
                        break;
                    }

                    O.Next();
                }
            break;

            case UPDATEOBJECT:
                SDLNet_TCP_Recv(socket, &upd, sizeof(updateObjectPackage));

                currentObject = NULL;
                O = *ListIterator<Object>(s->objectList).SetFirst();

                while(!O.IsLast())
                {
                    currentObject = O.GetCurrent();

                    if(currentObject->ID == upd.id)
                    {
                        currentObject->localPosition = upd.position;
                        currentObject->physObj->setImpulse(upd.impulse);
                        break;
                    }

                    O.Next();
                }
            break;

            default:
                printf("unknown signal recieved from server.\n");
            break;
        }
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
    strncpy(newobj.filename, object->objType->objectTypeFilename, 100);

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
    connSignal s = UPDATEOBJECT;
    struct updateObjectPackage updobj;

    updobj.id = object->ID;
    updobj.position = object->localPosition;
    updobj.impulse = object->physObj->getImpulse();

    SDLNet_TCP_Send(socket, &s, sizeof(connSignal));
    return SDLNet_TCP_Send(socket, &updobj, sizeof(struct updateObjectPackage));
}
