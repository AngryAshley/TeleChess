#include "ServerListener.h"

#include <iostream>

int main(int argc, char *argv[])
{
    ServerListener* sl;
    if (argc > 1 && *argv[1] == 'v')
    {
        sl = new ServerListener(1100, true);
    }
    else
    {
        sl = new ServerListener(1100, false);
    }
    
    std::cin.get();
    std::cout << "Messages received:\n";
    while (sl->Available())
    {
        std::cout << sl->GetCommand() << std::endl;
    }
    

    delete(sl);
    return 0;
}