#ifndef WEBPLAYER_H
#define WEBPLAYER_H

#include "IPlayer.h"
#include "IMatch.h"
#include "ServerListener.h"


class ServerListener;

class WebPlayer : public IPlayer
{
private:
    ServerListener* server;
    IMatch* match;
public:
    WebPlayer(ServerListener* server, int ID);
    bool Move(std::string move);
    bool OpponentMove(std::string move);

    void EnterMatch(IMatch* match);
    void LeaveMatch();

    ~WebPlayer();
};


#endif