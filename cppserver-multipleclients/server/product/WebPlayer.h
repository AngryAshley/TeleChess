#ifndef WEBPLAYER_H
#define WEBPLAYER_H

#include "IPlayer.h"
#include "IMatch.h"
#include "IMessenger.h"



class WebPlayer : public IPlayer
{
private:
    IMessenger* server;
    int clientNumber;
    IMatch* match;
    bool alive;
public:
    WebPlayer(IMessenger* server, int ID, int clientNumber);
    bool Move(std::string move);
    bool OpponentMove(std::string move);
    int getClientNr();

    void Revive(int clientNr);

    void EnterMatch(IMatch* match);
    void LeaveMatch();

    ~WebPlayer();
};


#endif