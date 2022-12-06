#ifndef MESSAGEINTERPRETER_H
#define MESSAGEINTERPRETER_H

#include "MatchMaker.h"

#include <string>

class MessageInterpreter
{
private:
    void Logon(std::string userID);
    void Logoff(std::string userID);
    void Join(std::string hostID);
    void Make(std::string game);
    void GameAction(std::string action);
    void KeepAlive();

    MatchMaker* matchMaker;

public:
    MessageInterpreter();
    void Receive(char* msg);
    ~MessageInterpreter();
};



#endif