#include "MessageInterpreter.h"

#define KEEPALIVE  0b00000001
#define LOGON      0b00000010
#define LOGOFF     0b00000011
#define MAKE       0b00000100
#define GAMEACTION 0b00000101
#define JOIN       0b00000110


void MessageInterpreter::Receive(char* msg)
{
    switch (msg[0])
    {
    case KEEPALIVE:
        KeepAlive();
        break;
    case LOGON:
        Logon(std::string(++msg));
        break;
    case LOGOFF:
        Logoff(std::string(++msg));
        break;
    case MAKE:
        Make(std::string(++msg));
        break;
    case GAMEACTION:
        GameAction(std::string(++msg));
        break;
    case JOIN:
        Join(std::string(++msg));
        break;
    
    default:
        break;
    }
}

void 