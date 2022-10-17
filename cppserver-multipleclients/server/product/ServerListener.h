#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <arpa/inet.h>

#define MAX_CLIENTS 40

class ServerListener
{
private:
    const uint16_t portNumber;
    fd_set sockets;
    int connectionSocket;
    struct sockaddr_in address;
    int clients[MAX_CLIENTS];
    int nrClients;
    int addClient(int client);
    void removeClient(int client);
public:
    ServerListener(uint16_t portNumber);
    void Start();
    void Listen();
    ~ServerListener();
};

#endif