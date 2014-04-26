#include <cstring>
#include <stdio.h>
#include <List.h>
#include <server.h>



void establishConnection(TCPsocket server, List<Client> *clist)
{
  TCPsocket client = SDLNet_TCP_Accept(server);
   if (client == NULL)
    return;
   printf("got a connection\n");


   loginPackage login;
   if(SDLNet_TCP_Recv(client, &login, sizeof(loginPackage))!= sizeof(loginPackage))
    {
        printf("no response from server\n");
        exit(-1);
    }

    printf("user %s logged in\n",login.name);


    connSignal response = SERVER;
    if(SDLNet_TCP_Send(client, &response, sizeof(connSignal)) != sizeof(connSignal))
    {
        printf("could not send data to server\n");
        exit(-1);
    }

    response = OK;
    if(SDLNet_TCP_Send(client, &response, sizeof(connSignal)) != sizeof(connSignal))
    {
        printf("could not send data to server\n");
        exit(-1);
    }

    printf("connection established!\n");
    Client *newClient = new Client();
    strncpy(newClient->name,login.name,20);
    newClient->connection = client;
    clist->PushFront(newClient);
}


int main(void)
{
	SDLNet_Init();

  IPaddress adress;
	TCPsocket server;

	if (SDLNet_ResolveHost (&adress, NULL, 9999) == -1)
  {
      printf ("SDLNet_ResolveHost: %s\n", SDLNet_GetError ());
      SDLNet_Quit ();
      exit (1);
  }

  server = SDLNet_TCP_Open (&adress);
  if (server == NULL)
  {
      printf ("ERR TCP_Open: %s\n", SDLNet_GetError ());
      SDLNet_Quit ();
      exit (-1);
  }

  List<Client> *clients = new List<Client>();

  while(1)
  {
    establishConnection(server,clients);
    SDL_Delay(100);
  }
  
   return 0;
}