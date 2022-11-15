#include "WebPlayer.h"

#include <iostream>

WebPlayer::WebPlayer(ServerListener* server, int ID)
:server(server)
{
    this->ID = ID;
}

WebPlayer::~WebPlayer()
{
    std::cout << "\33[4;31mPlayer " << ID << " disconnected\33[0m" << std::endl;
    if (inMatch)
    {
        match->Abort();
    }
}

void WebPlayer::EnterMatch(IMatch* match)
{
    this->match = match;
    inMatch = true;
}

void WebPlayer::LeaveMatch()
{
    this->match = nullptr;
    inMatch = false;
}

bool WebPlayer::Move(std::string move)
{
    return match->TryMove(move, this);
}

bool WebPlayer::OpponentMove(std::string move)
{
    return server->Send(GetID(), move);
}