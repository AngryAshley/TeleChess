#ifndef IMATCH_H
#define IMATCH_H

#include "Pieces.h"

#include <string>

class IMatch
{
public:
    virtual bool TryMove(Piece* boardBefore, Piece* boardAfter) = 0;
    virtual ~IMatch();
};

#endif