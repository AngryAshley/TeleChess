#ifndef IPLAYER_H
#define IPLAYER_H

#include "IMatch.h"

#include <string>

class IMatch;

class IPlayer
{
protected:
    int ID;
    bool inMatch = false;
public:
    int GetID() { return this->ID; }
    bool GetInMatch() { return inMatch; }
    
    virtual bool OpponentMove(std::string move) = 0;
    virtual void EnterMatch(IMatch* match) = 0;
    virtual void LeaveMatch() = 0;
    virtual ~IPlayer() {}
};

#endif