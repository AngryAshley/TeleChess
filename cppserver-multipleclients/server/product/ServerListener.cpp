#include "ServerListener.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

ServerListener::ServerListener(uint16_t portNumber, bool verbose)
:portNumber(portNumber)
,verbose(verbose)
{
    nrClients = 0;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i] = 0;
    }
    isListening = true;
    Start();
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

    listeningThread = std::thread(Listen, this);
    
}

void ServerListener::Listen(ServerListener* sl)
{
    while (sl->isListening)
    {
        fd_set sockets;

        FD_ZERO(&sockets);
        FD_SET(sl->connectionSocket, &sockets);

        for (int i = 0; i < sl->nrClients; i++)
        {
            FD_SET(sl->clients[i], &sockets);
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
            if (sl->verbose)
            {
                std::cout << "listening..." << std::endl;
            }
        }
        else
        {
            if (FD_ISSET(sl->connectionSocket, &sockets))
            {
                int newSocket = accept(sl->connectionSocket, NULL, NULL);
                if (newSocket < 0)
                {
                    perror("accept failed");
                }
                if (sl->addClient(newSocket) < 0)
                {
                    if (sl->verbose)
                    {
                        std::cout << "max number of clients reached" << std::endl;
                    }
                }
                else
                {
                    if (sl->verbose)
                    {
                        std::cout << "new client: " << newSocket << " added" << std::endl;
                    }
                }
            }
            for (int i = 0; i < sl->nrClients; i++)
            {
                if (FD_ISSET(sl->clients[i], &sockets))
                {
                    char buf[100];
                    int nrBytes = read(sl->clients[i], buf, 99);
                    if (nrBytes > 0)
                    {
                        buf[nrBytes] = '\0';
                        if (sl->verbose)
                        {
                            std::cout << "From: " << sl->clients[i] << " received " << nrBytes << " bytes: " << buf << std::endl;
                            send(sl->clients[i], buf, nrBytes, 0);
                        }
                        std::string cmd = std::to_string(sl->clients[i]) + " " + std::string(buf);
                        sl->messageQueue.insert(sl->messageQueue.begin(), cmd);
                    }
                    else if (nrBytes == 0)
                    {
                        sl->removeClient(sl->clients[i]);
                        if (sl->verbose)
                        {
                            std::cout << "client: " << sl->clients[i] << " dropped\n";
                            std::cout << "Remaining:\n";
                            for (int j = 0; j < sl->nrClients; j++)
                            {
                                std::cout << "\tclient: " << sl->clients[j] << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

void ServerListener::Stop()
{
    isListening = false;
    listeningThread.join();
}

bool ServerListener::Available()
{
    return !(messageQueue.empty());
}

std::string ServerListener::GetCommand()
{
    if (Available())
    {
        std::string cmd = messageQueue.back();
        messageQueue.pop_back();
        return cmd;
    }
    return NULL;
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

ServerListener::~ServerListener()
{
    Stop();
}