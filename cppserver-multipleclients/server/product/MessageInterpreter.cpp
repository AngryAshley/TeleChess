#include "MessageInterpreter.h"

#define KEEPALIVE  0b00000001
#define LOGON      0b00000010
#define LOGOFF     0b00000011
#define MAKE       0b00000100
#define GAMEACTION 0b00000101
#define JOIN       0b00000110


void MessageInterpreter::Receive(char* msg, int clientNr)
{
    switch (msg[0])
    {
    case KEEPALIVE:
        KeepAlive(std::string(++msg));
        break;
    case LOGON:
        Logon(std::string(++msg), clientNr);
        break;
    case LOGOFF:
        Logoff(std::string(++msg));
        break;
    case MAKE:
        Make(std::string(++msg));
        break;
    case GAMEACTION:
        GameAction(std::string(++msg));
        break;
    case JOIN:
        Join(std::string(++msg));
        break;
    
    default:
        break;
    }
}

void MessageInterpreter::KeepAlive(std::string userID)
{
    
}

void MessageInterpreter::Logon(std::string userID, int clientNr)
{
    int logOnID = std::stoi(userID);
    for (auto & player : players)
    {
        if (player->GetID() == logOnID)
        {
            player->Revive(clientNr);
            return;
        }
    }
    WebPlayer* newPlayer = new WebPlayer(server, logOnID, clientNr);
    players.push_back(newPlayer);
}

void MessageInterpreter::Logoff(std::string userID)
{
    int LogOffID = std::stoi(userID);
    for (unsigned long int i = 0; i < players.size(); i++)
    {
        if (players[i]->GetID() == LogOffID)
        {
            WebPlayer* player = players[i];
            players.erase(players.begin() + i);
            delete(player);
        }
    }    
}

void MessageInterpreter::Make(std::string startAsWhite)
{
    matchMaker->NewMatchRequest()
}
