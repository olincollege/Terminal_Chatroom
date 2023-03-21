#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define MAX_MESSAGE_LENGTH 1024

// Functions

/**
 * Send a received message to all connected clients
 * 
 * @param senderIdx: An int representing the client in the client list that sent the message
 * @param client_socket_list: A list of ints which are the connected client sockets
 * @param buffer: a character array that stores the message to be broadcastes
**/
void broadcast_data(int senderIdx, int client_socket_list[MAX_CLIENTS], char buffer[MAX_MESSAGE_LENGTH]);

/**
 * Handle the data the server reads from the socket. This can be a new message or connection request.
 * 
 * @param client_socket_list: A list of ints which are the connected client sockets
 * @param read_socket: An fd_set pointer that points to the socket which the server detected had new data
 * @param buffer: a character array that stores the message to be broadcastes
 * @param current_client: An int representing the client in the client list that sent the message
**/
void handle_receive(int client_socket_list[MAX_CLIENTS], fd_set *read_socket, char buffer[MAX_MESSAGE_LENGTH], int current_client);

/**
 * Check if any of the client sockets has new data to give to server.
 * 
 * @param client_socket_list: A list of ints which are the connected client sockets
 * @param read_socket: An fd_set pointer that points to the socket which the server detected had new data
 * @param write_socket: An fd_set pointer that points to the socket which the server should write new data to
 * 
**/
void check_read_sockets(int client_socket_list[MAX_CLIENTS], fd_set *read_socket, fd_set *write_socket);

/**
 * Add new connected client to clients list and check if connection was successful
 * 
 * @param client_socket_list: A list of ints which are the connected client sockets
 * @param server_socket: An int representing the server socket
**/
void new_client_connection(int client_socket_list[MAX_CLIENTS], int server_socket);

/**
 * Set up the server socket with correct, non-blocking parameters
 * 
 * @return: An int storing the socket nummber of the server socket
**/
int setup_server_socket();

/**
 * Check that server socket binds and listens properly, sends appropriate errors if not
 * 
 * @param bind_status: An int that's < 0 if the bind failed
 * @param listen_status: An int that's < 0 if the listen failed
**/
void check_socket_bind_listen(int bind_status, int listen_status);

/**
 * Refresh the read and write sockets to prepare for data
 * 
 * @param read_socket: An fd_set pointer that points to the socket which the server detected had new data
 * @param write_socket: An fd_set pointer that points to the socket which the server should write new data to
 * @param server_socket: An int representing the server socket
 * @param client_socket_list: A list of ints which are the connected client sockets
 * @param tv: A timeval that stores the timeout after which the server will refresh the sockets again
**/
void refresh_sockets(fd_set read_socket, fd_set write_socket,
                    int server_socket, int client_socket_list[MAX_CLIENTS],
                    struct timeval tv);



#endif // SERVER_H
