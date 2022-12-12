#ifndef MESSAGEINTERPRETER_H
#define MESSAGEINTERPRETER_H

#include "MatchMaker.h"
#include "WebPlayer.h"
#include "IMessenger.h"

#include <string>
#include <vector>

class MessageInterpreter
{
private:
    void Logon(std::string userID, int clientNr);
    void Logoff(std::string userID);
    void Join(std::string hostID);
    void Make(std::string game);
    void GameAction(std::string action);
    void KeepAlive(std::string userID);

    MatchMaker* matchMaker;
    IMessenger* server;
    std::vector<WebPlayer*> players;

public:
    MessageInterpreter();
    void Receive(char* msg, int clientNr);
    ~MessageInterpreter();
};



#endif