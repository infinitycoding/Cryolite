#include <cstring>
#include <stdio.h>
#include <Net.h>

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


	TCPsocket client = SDLNet_TCP_Accept(server);
   while (client == NULL)
   {
       /* eine Sekunde warten */
       SDL_Delay (100);
       client = SDLNet_TCP_Accept (server);
   }
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

    
    while(1);
       


   return 0;
}