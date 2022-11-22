#include "ServerListener.h"
#include "MatchMaker.h"

#include <iostream>

int main(int argc, char *argv[])
{
    ServerListener* sl;
    MatchMaker* mm = new MatchMaker();
    MReferee* ref = new MReferee();

    if (argc > 1 && *argv[1] == 'v')
    {
        sl = new ServerListener(1100, true, mm);
    }
    else
    {
        sl = new ServerListener(1100, false, mm);
    }
    
    while (true)
    {
        mm->checkForAvailablePlayers(ref);
    }
    // std::cin.get();

    delete(sl);
    return 0;
}