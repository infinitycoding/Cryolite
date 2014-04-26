#include <cstring>
#include <stdio.h>
#include <List.h>
#include <server.h>
#include <object.h>



void establishConnection(SDLNet_SocketSet *set, TCPsocket server, List<Client> *clist)
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
    SDLNet_TCP_AddSocket (*set, client);
}

void handleData(SDLNet_SocketSet *set, List<Client> *clist, List<ServerObject> *objects, List<Job> *joblist)
{
  if(SDLNet_CheckSockets(*set,10))
  {
      ListIterator<Client> i = ListIterator<Client>(clist);
      i.SetFirst();
      while(!i.IsLast() && !i.IsEmpty())
      {

        Client *currentClient = i.GetCurrent();
        if(SDLNet_SocketReady(currentClient->connection))
        {
          connSignal sig = NOSIGNAL;
          if(SDLNet_TCP_Recv(currentClient->connection, &sig, sizeof(connSignal))!= sizeof(connSignal))
          {
            printf("Error: no response from client %s\n",currentClient->name);
            i.Remove();
          }

          if(sig == ADDOBJECT)
          {
              addObjectPackage pck;
              if(SDLNet_TCP_Recv(currentClient->connection, &pck, sizeof(addObjectPackage))!= sizeof(addObjectPackage))
              {
                  printf("Error: invalid response from client %s\n",currentClient->name);
                  i.Remove();
              }
              ServerObject *newObj = new ServerObject;
              newObj->obj = pck;
              newObj->player = currentClient;
              objects->PushFront(newObj);
              Job *newJob = new Job;
              newJob->type = ADDOBJECT;
              newJob->player = currentClient;
              newJob->obj = newObj;
              joblist->PushFront(newJob);
              printf("new Object recieved client:%s id:%d type:%s\n",currentClient->name,pck.id,pck.objtype);
          }

          if(sig == REMOVEOBJECT)
          {
              deleteObjectPackage pck;
              if(SDLNet_TCP_Recv(currentClient->connection, &pck, sizeof(deleteObjectPackage))!= sizeof(deleteObjectPackage))
              {
                  printf("Error: invalid response from client %s\n",currentClient->name);
                  i.Remove();
              }

              ListIterator<ServerObject> o = ListIterator<ServerObject>(objects);
              o.SetFirst();
              while(!o.IsLast() && !o.IsEmpty())
              {
                if(o.GetCurrent()->obj.id == pck.id)
                  {
                    Job *newJob = new Job;
                    newJob->type = REMOVEOBJECT;
                    newJob->player = currentClient;
                    newJob->obj = o.GetCurrent();
                    joblist->PushFront(newJob);
                    break;
                }
                o.Next();
              }

            printf("delete object client:%s id:%d\n",currentClient->name,pck.id);
          }

          if(sig == UPDATEOBJECT)
          {
              updateObjectPackage pck;
              if(SDLNet_TCP_Recv(currentClient->connection, &pck, sizeof(updateObjectPackage))!= sizeof(updateObjectPackage))
              {
                  printf("Error: invalid response from client %s\n",currentClient->name);
                  i.Remove();
              }

              ListIterator<ServerObject> o = ListIterator<ServerObject>(objects);
              o.SetFirst();
              while(!o.IsLast() && !o.IsEmpty())
              {
                if(o.GetCurrent()->obj.id == pck.id)
                {
                    Job *newJob = new Job;
                    newJob->type = UPDATEOBJECT;
                    newJob->player = currentClient;
                    newJob->obj = o.GetCurrent();
                    newJob->obj->obj.position = pck.position;
                    newJob->obj->obj.impulse = pck.impulse;
                    joblist->PushFront(newJob);
                    break;
                }
                  
                o.Next();
              }



            printf("update object client:%s id:%d\n",currentClient->name,pck.id);
          }



        }

        i.Next();
      }
  }
}

void doJobs(SDLNet_SocketSet *set, List<Client> *clist, List<ServerObject> *objects, List<Job> *joblist)
{
    
    while(!joblist->IsEmpty())
    {
      Job *currentJob = joblist->PopFront();

      if(currentJob->type == ADDOBJECT)
      {
          ListIterator<Client> c = ListIterator<Client>(clist);
          c.SetFirst();
          while(!c.IsLast() && !c.IsEmpty())
          {
              Client *currentClient = c.GetCurrent();
              if(currentClient != currentJob->player)
              {
                  printf("send add Job to %s \n",currentClient->name);
                  if(SDLNet_TCP_Send(currentClient->connection, &currentJob->type, sizeof(connSignal)) != sizeof(connSignal))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }

                  if(SDLNet_TCP_Send(currentClient->connection, &currentJob->obj->obj, sizeof(addObjectPackage)) != sizeof(addObjectPackage))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }
              }
              c.Next();
          }
      }

      if(currentJob->type == REMOVEOBJECT)
      {
          ListIterator<Client> c = ListIterator<Client>(clist);
          c.SetFirst();
          while(!c.IsLast() && !c.IsEmpty())
          {
              Client *currentClient = c.GetCurrent();
              if(currentClient != currentJob->player)
              {
                  printf("send add Job to %s \n",currentClient->name);
                  if(SDLNet_TCP_Send(currentClient->connection, &currentJob->type, sizeof(connSignal)) != sizeof(connSignal))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }

                  if(SDLNet_TCP_Send(currentClient->connection, &currentJob->obj->obj.id, sizeof(deleteObjectPackage)) != sizeof(deleteObjectPackage))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }
              }
              c.Next();
          }

          ListIterator<ServerObject> o = ListIterator<ServerObject>(objects);
          o.SetFirst();
          while(!o.IsLast() && !o.IsEmpty())
          {
            if(o.GetCurrent() == currentJob->obj)
            {
              o.Remove();
              delete currentJob->obj;
              break;
            }
            o.Next();
          }


      }

      if(currentJob->type == UPDATEOBJECT)
      {
          ListIterator<Client> c = ListIterator<Client>(clist);
          c.SetFirst();
          while(!c.IsLast() && !c.IsEmpty())
          {
              Client *currentClient = c.GetCurrent();
              if(currentClient != currentJob->player)
              {
                  printf("send add Job to %s \n",currentClient->name);
                  if(SDLNet_TCP_Send(currentClient->connection, &currentJob->type, sizeof(connSignal)) != sizeof(connSignal))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }

                  updateObjectPackage pck;
                  pck.id = currentJob->obj->obj.id;
                  pck.position = currentJob->obj->obj.position;
                  pck.impulse = currentJob->obj->obj.impulse;

                  if(SDLNet_TCP_Send(currentClient->connection, &pck, sizeof(updateObjectPackage)) != sizeof(updateObjectPackage))
                  {
                      printf("could not send data to client %s\n",currentClient->name);
                  }
              }
              c.Next();
          }
      }

      delete currentJob;
    }


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
  List<ServerObject> *objects = new List<ServerObject>();
  List<Job> *Jobs = new List<Job>();
  SDLNet_SocketSet set = SDLNet_AllocSocketSet (10);

  while(1)
  {
    establishConnection(&set, server, clients);
    handleData(&set, clients, objects, Jobs);
    doJobs(&set, clients, objects, Jobs);
    SDL_Delay(10);
  }
  
   return 0;
}

