#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <Match.h>

#include <vector>

class MatchMaker
{
private:
    std::vector<Match> matches;
    
public:
    MatchMaker();
    ~MatchMaker();
};

#endif