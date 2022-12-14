#include "MatchMaker.h"
#include <iostream>

MatchMaker::MatchMaker()
{
    
}



void MatchMaker::NewMatch(MatchRequest request, IPlayer* opponent)
{
    const std::lock_guard<std::mutex> lock(mtx);
    Match* newMatch = nullptr;
    if (request.getStartAsWhite())
    {
        newMatch = new Match(request.getReferee(), request.getPlayer(), opponent);

    }
    else
    {
        newMatch = new Match(request.getReferee(), opponent, request.getPlayer());
    }

    if (newMatch != nullptr)
    {
        matches.push_back(newMatch);
    }
}

void MatchMaker::NewMatchRequest(IReferee* referee, IPlayer* player, bool startAsWhite)
{
    const std::lock_guard<std::mutex> lock(mtx);
    if(findRequest(player) == nullptr)
    {
        return;
    }
    MatchRequest newRequest = MatchRequest(referee, player, startAsWhite);
    requests.push_back(newRequest);
}

MatchRequest* MatchMaker::findRequest(IPlayer* player)
{
    for (auto & request : requests)
    {
        if (request.getPlayer() == player)
        {
            return &request;
        }
    }
    return nullptr;
}

bool MatchMaker::JoinMatch(IPlayer* opponent, IPlayer* player)
{
    if (opponent == nullptr || player == nullptr)
    {
        return false;
    }

    MatchRequest* request = findRequest(opponent);
    if (request == nullptr)
    {
        return false;
    }

    NewMatch(*request, player);
    return true;
}