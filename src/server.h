#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT_NUMBER 12345
#define MAX_CLIENTS 5
#define MAX_MESSAGE_LENGTH 1024

// Function prototypes
void startServer();

#endif // SERVER_H
