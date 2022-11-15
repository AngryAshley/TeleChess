#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <arpa/inet.h>
#include <thread>
#include <vector>

#define MAX_CLIENTS 40

class ServerListener
{
private:
    const uint16_t portNumber;
    const bool verbose;

    fd_set sockets;
    int connectionSocket;
    struct sockaddr_in address;

    int clients[MAX_CLIENTS];
    int nrClients;
    int addClient(int client);
    void removeClient(int client);

    std::thread listeningThread;
    std::vector<std::string> messageQueue;

    void Start();
    static void Listen(ServerListener*);
    bool isListening;
    void Stop();
public:
    ServerListener(uint16_t portNumber, bool verbose);
    bool Available();
    std::string GetCommand();
    ~ServerListener();
};

#endif