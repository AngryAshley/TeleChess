#ifndef MATCHREQUEST_H
#define MATCHREQUEST_H

#include "IPlayer.h"
#include "IReferee.h"

class MatchRequest
{
private:
    IReferee* referee;
    IPlayer* player;
    bool startAsWhite;

public:
    IPlayer* getPlayer() { return player; }
    IReferee* getReferee() { return referee; }
    bool getStartAsWhite() { return startAsWhite; }
    MatchRequest(IReferee* referee, IPlayer* player, bool startAsWhite);
    // ~MatchRequest(){}
};


#endif