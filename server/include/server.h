#ifndef SERVER_H
#define SERVER_H

#include <Net.h>
#include <scene.h>
#include <SDL_net.h>


class Client
{
	public:
		char name[20];
		TCPsocket connection;
};




#endif