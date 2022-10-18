#include "ServerListener.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

ServerListener::ServerListener(uint16_t portNumber)
:portNumber(portNumber)
{
    nrClients = 0;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i] = 0;
    }
}

void ServerListener::Start()
{
    connectionSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectionSocket < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    int opt = true;

    if( setsockopt(connectionSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(portNumber);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(connectionSocket, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(connectionSocket, 4) < 0)
    {
        perror("listen failed");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }


    
}

void ServerListener::Listen()
{
    fd_set sockets;

    FD_ZERO(&sockets);
    FD_SET(connectionSocket, &sockets);

    for (int i = 0; i < nrClients; i++)
    {
        FD_SET(clients[i], &sockets);
    }

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    int nrSockets = select(FD_SETSIZE, &sockets, NULL, NULL, &timeout);

    if (nrSockets < 0)
    {
        perror("error from calling socket");
    }
    else if (nrSockets == 0)
    {
        std::cout << "listening..." << std::endl;
    }
    else
    {
        if (FD_ISSET(connectionSocket, &sockets))
        {
            int newSocket = accept(connectionSocket, NULL, NULL);
            if (newSocket < 0)
            {
                perror("accept failed");
            }
            if (addClient(newSocket) < 0)
            {
                std::cout << "max number of clients reached" << std::endl;
            }
            else
            {
                std::cout << "new client: " << newSocket << " added" << std::endl;
            }
        }
        for (int i = 0; i < nrClients; i++)
        {
            if (FD_ISSET(clients[i], &sockets))
            {
                char buf[100];
                int nrBytes = read(clients[i], buf, 99);
                if (nrBytes > 0)
                {
                    buf[nrBytes] = '\0';
                    std::cout << "From: " << clients[i] << " received " << nrBytes << " bytes: " << buf << std::endl;
                    send(clients[i], buf, nrBytes, 0);
                }
                else if (nrBytes == 0)
                {
                    std::cout << "client: " << clients[i] << " dropped\n";
                    removeClient(clients[i]);

                    for (int j = 0; j < nrClients; j++)
                    {
                        std::cout << "client: " << clients[i] << std::endl;
                    }
                }
            }
        }
    }
}

int ServerListener::addClient(int client)
{
    if (nrClients >= MAX_CLIENTS)
    {
        return -1;
    }
    clients[nrClients++] = client;
    return 0;
}

void ServerListener::removeClient(int client)
{
    bool found = false;
    for (int i = 0; i < nrClients; i++)
    {
        if (!found)
        {
            if (clients[i] == client)
            {
                found = true;
                clients[i] = clients[i + 1];
            }
        }
        else if (i + 1 < MAX_CLIENTS)
        {
            clients[i] = clients[i + 1];
        }
    }
    if (found)
    {
        clients[nrClients--] = 0;
    }
}