#ifndef MATCH_H
#define MATCH_H

#include "IReferee.h"
#include "IMatch.h"
#include "IPlayer.h"

#include <string>

class Match : public IMatch
{
private:    
    IReferee* referee;
    IPlayer* playerWhite;
    IPlayer* playerBlack;
    IPlayer* playerToMove;

public:
    bool TryMove(std::string move, IPlayer* player);
    void Abort();
    Match(IReferee* referee, IPlayer* playerWhite, IPlayer* playerBlack);
    ~Match();
};

#endif