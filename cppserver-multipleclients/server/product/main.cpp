#include "ServerListener.h"

#include <iostream>

int main()
{
    ServerListener* sl = new ServerListener(1100);

    sl->Start();
    while(true)
    {
        sl->Listen();
    }
    return 0;
}