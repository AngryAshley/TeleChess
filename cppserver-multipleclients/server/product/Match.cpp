#include "Match.h"

#include <iostream>

Match::Match(IReferee* referee, IPlayer* playerWhite, IPlayer* playerBlack)
:referee(referee)
,playerWhite(playerWhite)
,playerBlack(playerBlack)
{
    playerToMove = playerWhite;
    std::cout << "Match made between client " << playerWhite->GetID() << " and " << playerBlack->GetID() << std::endl;
}

bool Match::TryMove(std::string move, IPlayer* player)
{ 
    if (player != playerToMove || !referee->CheckMove(move))
    {
        return false;
    }

    if (player == playerWhite)
    {
        playerBlack->OpponentMove(move);
        playerToMove = playerBlack;
        return true;
    }
    
    if (player == playerBlack)
    {
        playerWhite->OpponentMove(move);
        playerToMove = playerWhite;
        return true;
    }
    return false;
}

Match::~Match()
{

}

void Match::Abort()
{
    std::cout << "\33[0;32mMatch aborted\33[0m" << std::endl;
    playerWhite->LeaveMatch();
    playerBlack->LeaveMatch();
    delete(this);
}