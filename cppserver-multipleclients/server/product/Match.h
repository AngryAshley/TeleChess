#ifndef MATCH_H
#define MATCH_H

#include "IReferee.h"
#include "IMatch.h"
#include "IPlayer.h"

#include <string>

class Match : IMatch
{
private:
    const int nrPlayers;
    
    IReferee referee;
    IPlayer* players;
    int playerToMove = 0;

    Piece* currentBoard;
public:
    bool TryMove(Piece* boardBefore, Piece* boardAfter, IPlayer *player);
    Match(IReferee referee, IPlayer* players, int nrPlayers);
    ~Match();
};

#endif