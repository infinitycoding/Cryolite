#ifndef SERVER_H
#define SERVER_H

#include <Net.h>
#include <scene.h>
#include <SDL_net.h>



struct Client
{
		char name[20];
		TCPsocket connection;
};


struct ServerObject
{
		addObjectPackage obj;
    	Client *player;
};

struct Job
{
	connSignal type;
	Client *player;
	ServerObject *obj;
};



#endif