#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Set the maximum input size that shout can read.
enum { 
    USERNAME_BUFFER_SIZE = 16,
    TIMESTAMP_BUFFER_SIZE = 8
    };

/**
 * Checks if the socket was created successfully, throws an error if not.
 *
 * @param sockfd An integer representing the socket.
 */
void check_socket_creation(int);

/**
 * Checks if a connection was made to the server successfully, throws an
 * error if not.
 *
 * @param connection_status An integer representing the connection status.
 */
void check_connection_status(int);

#endif
