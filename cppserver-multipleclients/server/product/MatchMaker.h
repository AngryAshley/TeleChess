#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "Match.h"
#include "IMatch.h"

#include <vector>

class MatchMaker
{
private:
    std::vector<Match*> matches;
    std::vector<IPlayer*> players;
public:
    void checkForAvailablePlayers(IReferee* referee);
    void AddPlayer(IPlayer* player);
    void RemovePlayer(IPlayer* player);
    MatchMaker();
    void NewMatch(IReferee* referee, IPlayer* playerWhite, IPlayer* playerBlack);
    ~MatchMaker();
};

#endif