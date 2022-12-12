#include "MatchRequest.h"

MatchRequest::MatchRequest(IReferee* referee, IPlayer* player, bool startAsWhite)
: referee(referee)
, player(player)
, startAsWhite(startAsWhite)
{

}