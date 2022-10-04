#include <iostream> 
#include <vector>
#include <algorithm>
#include "connection.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib> 
#include <iostream> 
#include <unistd.h> 

using namespace std;

vector<int> ports;

int StartConnection( int port, connection_data *connection);

int main(int argc, char** argv) 
{   
    connection_data connection;
    int port = 50000;
    StartConnection(port, &connection);
    
    return 0;
}

int StartConnection( int port, connection_data *connection){
    if(port <= 0 || connection == NULL){
        return -1;
    }

    if(count(ports.begin(), ports.end(), port)){
        cout << "Port " << port << " is already in use" << endl;
        return -1;
    }
    else{
        if( CreateConnection(port, connection) == 0){
            ports.push_back(port);
            return 0;
        }
        else{
            cout << "Failed to create Connection on port " << port << endl;
            return -1;
        }
    }
}
