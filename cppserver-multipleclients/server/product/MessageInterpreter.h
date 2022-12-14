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
    void Join(std::string hostID, int clientNr);
    void Make(std::string game, int clientNr);
    void GameAction(std::string action, int clientNr);
    void KeepAlive(std::string userID);
    IPlayer* GetPlayerByClientNr(int clientNr);

    MatchMaker* matchMaker;
    IMessenger* server;
    std::vector<WebPlayer*> players;

public:
    MessageInterpreter(MatchMaker* matchmaker, IMessenger* server);
    void Receive(char* msg, int clientNr);
    ~MessageInterpreter();
};



#endif