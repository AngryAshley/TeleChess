#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

const uint16_t PortNumber = 1100;

void Listen(int socketFd)
{
    while (true)
    {
        char buf[100] = {0};	
        int bytes = read(socketFd, buf, 100);
        if (bytes > 0)
        {
            std::cout << "received " << bytes << " bytes: " << buf << std::endl;
        }
        else if (bytes == 0)
        {
            std::cout << "connection closed" << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("read failed");
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    int socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd == -1)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PortNumber);

    int result = inet_pton(AF_INET, argv[1], &sa.sin_addr);
    if (result != 1)
    {
        perror("could not convert ip address to network address structure");
        exit(EXIT_FAILURE);
    }
    else
    {
        result = connect(socketFd, (struct sockaddr*)&sa, sizeof sa);

        if (result < 0)
        {
            perror("connect failed");
            close(socketFd);
            exit(EXIT_FAILURE);
        }
        
        std::thread listenThread = std::thread(Listen, socketFd);
        std::string text = "";
        while (true)
        {
            text = "";
            std::cin >> text;
            size_t nrBytes = send(socketFd, text.c_str(), text.length(), 0);
            if (nrBytes != text.length())
            {
                std::cout << "not everything is sent (" << nrBytes << "/" << text.length() << " bytes sent)\n";
            }
            
        }

        if (shutdown(socketFd, SHUT_RDWR) < 0)
        {
            perror("shutdown failed");
            close(socketFd);
            exit(EXIT_FAILURE);
        }

        close(socketFd);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
