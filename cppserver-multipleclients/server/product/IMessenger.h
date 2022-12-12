#ifndef IMESSENGER_H
#define IMESSENGER_H

#include <string>

class IMessenger
{
public:
    virtual bool Send(int clientSocket, std::string message) = 0;
    virtual ~IMessenger();
};

#endif