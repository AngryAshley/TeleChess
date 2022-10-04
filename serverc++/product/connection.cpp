#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib> 
#include <iostream> 
#include <unistd.h> 

#include "connection.h"

using namespace std;


int CreateConnection(int server_port, connection_data *connection){
    //check if port is legal
    if(server_port <= 0 || connection == NULL){
        return -1;
    }

    try{
        if(server_port <= 0){
            throw (server_port);
        }
    }
    catch(int portError){
        cout << "Invalid port number "<< portError << endl;
        return -1;
    }

    // Create socket
    int resultSockCreate = socket( AF_INET, SOCK_STREAM, 0);
    try{
        if(resultSockCreate < 0){
            throw (resultSockCreate);
        }
    }
    catch(int socketError){
        cout << "Something went wrong creating a socket. Result: "<< socketError << endl;
        return -1;
    }

    //bind socket to port
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr.sin_port = htons(server_port); 

    int resultBind = bind(resultSockCreate, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    try{
        if(resultBind < 0){
            throw (resultBind);
        }
    }
    catch(int bindError){
        cout << "Something went wrong binding the server to socket " << resultSockCreate << ". Result: "<< bindError << endl;
        return -1;
    }

    connection->port = server_port;
    connection->socket = resultSockCreate;

    //listen for 3 connection requests
    int resultListen = listen(connection->socket, 3); 
    if(resultListen < 0){
        cout << "Failed to listen on socket. errno: " << errno << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Listening succesfull" << endl;
        cout << "Listen Result: " << resultListen << endl;
    }
    

    // Grab a connection from the queue
    auto addrlen = sizeof(sockaddr);
    int connectionint = accept(connection->socket, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if (connectionint < 0) {
        cout << "Failed to grab connection. errno: " << errno << endl;
        exit(EXIT_FAILURE);
    }
    else{
        cout << "Accepted connection" << endl;
    }
    
    //close the connection and socket
    close(connectionint);
    close(resultSockCreate);

    return 0;
}