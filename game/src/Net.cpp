#include <cstring>
#include <Net.h>


Net::Net(unsigned char ip0, unsigned char ip1, unsigned char ip2, unsigned char ip3, unsigned short serverPort, const char *username)
{
    serverIP.host = (ip3<<24) | (ip2<<16) | (ip1<<8) | ip0;
    serverIP.port = serverPort;
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
