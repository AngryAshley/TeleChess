#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "Match.h"
#include "IMatch.h"
#include "MatchRequest.h"

#include <vector>
#include <mutex>

class MatchMaker
{
private:
    std::vector<Match*> matches;
    std::vector<MatchRequest> requests;
    std::mutex mtx;
    MatchRequest* findRequest(IPlayer* player);
    IPlayer* findPlayer(int userID);
    void NewMatch(MatchRequest request, IPlayer* opponent);
public:

    MatchMaker();
    void NewMatchRequest(IReferee* referee, IPlayer* player, bool startAsWhite);
    bool JoinMatch(int userId, IPlayer* player);
    ~MatchMaker();
};

#endif