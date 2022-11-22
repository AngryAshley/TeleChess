#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include "WebPlayer.h"
#include "MatchMaker.h"

#include <arpa/inet.h>
#include <thread>
#include <vector>

#define MAX_CLIENTS 40

class WebPlayer;

class ServerListener
{
private:
    const uint16_t portNumber;
    const bool verbose;
    MatchMaker* matchmaker;

    fd_set sockets;
    int connectionSocket;
    struct sockaddr_in address;

    WebPlayer* clients[MAX_CLIENTS];
    int nrClients;
    int addClient(int client);
    void removeClient(int client);
    WebPlayer* getClient(int client);

    std::thread listeningThread;
    std::vector<std::string> messageQueue;

    void Start();
    static void Listen(ServerListener*);
    bool isListening;
    void Stop();
public:
    ServerListener(uint16_t portNumber, bool verbose, MatchMaker* matchmaker);
    bool Available();
    std::string GetCommand();
    bool Send(int clientID, std::string &message);
    ~ServerListener();
};

#endif