#ifndef IMATCH_H
#define IMATCH_H

#include "IPlayer.h"

#include <string>

class IPlayer;

class IMatch
{
public:
    virtual bool TryMove(std::string move, IPlayer* player) = 0;
    virtual void Abort() = 0;
    virtual ~IMatch() {}
};

#endif