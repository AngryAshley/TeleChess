#ifndef IREFEREE_H
#define IREFEREE_H

#include "Pieces.h"

class IReferee
{
public:
    virtual bool CheckMove(Piece* boardBefore, Piece* boardAfter);
    virtual Piece* CreateBoard();
    virtual ~IReferee();
};

#endif