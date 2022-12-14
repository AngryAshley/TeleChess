#include "MessageInterpreter.h"
#include "IReferee.h"

#define KEEPALIVE  0b00000001
#define LOGON      0b00000010
#define LOGOFF     0b00000011
#define MAKE       0b00000100
#define GAMEACTION 0b00000101
#define JOIN       0b00000110


MessageInterpreter::MessageInterpreter(MatchMaker* matchMaker, IMessenger* server)
:matchMaker(matchMaker)
,server(server)
{

}

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
        Make(std::string(++msg), clientNr);
        break;
    case GAMEACTION:
        GameAction(std::string(++msg), clientNr);
        break;
    case JOIN:
        Join(std::string(++msg), clientNr);
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

IPlayer* MessageInterpreter::GetPlayerByClientNr(int clientNr)
{
    IPlayer* playerFound = nullptr;
    for (auto & player : players)
    {
        if (player->getClientNr() == clientNr)
        {
            playerFound = player;
        }
    }
    
    return playerFound;
}



void MessageInterpreter::Make(std::string startAsWhite, int clientNr)
{
    IPlayer* player = GetPlayerByClientNr(clientNr);
    if (player == nullptr)
    {
        return;
    }

    matchMaker->NewMatchRequest(new MReferee, player, stoi(startAsWhite));
}

void MessageInterpreter::Join(std::string userID, int clientNr)
{
    int opponentID = std::stoi(userID);
    IPlayer* player = GetPlayerByClientNr(clientNr);
    if (player == nullptr)
    {
        return;
    }

    IPlayer* opponent = GetPlayerByClientNr(opponentID);
    if (opponent == nullptr)
    {
        return;
    }

    matchMaker->JoinMatch(opponent, player);

}

void MessageInterpreter::GameAction(std::string move, int clientNr)
{
    IPlayer* player = GetPlayerByClientNr(clientNr);
    if (player == nullptr)
    {
        return;
    }

    player->Move(move);
}
