#include "Match.h"

bool Match::TryMove(Piece* boardBefore, Piece* boardAfter, IPlayer* player)
{
    if (!(*player == players[playerToMove]))
    {
        return false;
    }
    if (referee.CheckMove(boardBefore, boardAfter))
    {
        return false;
    }
     
    return true;
}