#ifndef CONNECTION_H
#define CONNECTION_H

typedef struct {
    int port;
    int socket;
    int connection;
}connection_data;


int CreateConnection(int server_port, connection_data *connection);

#endif