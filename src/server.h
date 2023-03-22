#ifndef SERVER_H
#define SERVER_H

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

typedef enum {
  PORT = 8080,
  MAX_MESSAGE_LENGTH = 1024,
  MAX_CLIENTS = 5,
  TV_USEC = 10000
} Constants;

// Functions

/**
 * Send a received message to all connected clients.
 *
 * @param client_socket_list: A list of ints which are the connected client
 *                            sockets.
 * @param buffer: a character array that stores the message to be broadcasts.
 **/
void broadcast_data(int client_socket_list[MAX_CLIENTS],
                    char buffer[MAX_MESSAGE_LENGTH]);

/**
 * Handle the data the server reads from the socket. This can be a new message
 * or connection request.
 *
 * @param client_socket_list: A list of ints which are the connected client
 *                            sockets.
 * @param buffer: a character array that stores the message to be broadcasts
 * @param current_client: An int representing the client in the client list that
 *                        sent the message.
 **/
void handle_receive(int client_socket_list[MAX_CLIENTS],
                    char buffer[MAX_MESSAGE_LENGTH], int current_client);

/**
 * Check if any of the client sockets has new data to give to server.
 *
 * @param client_socket_list: A list of ints which are the connected client
 *                            sockets.
 * @param read_socket: An fd_set pointer that points to the socket which the
 *                     server detected had new data.
 * @param buffer: An fd_set pointer that points to the socket which the
 *                server should write new data to.
 *
 **/
void check_read_sockets(int client_socket_list[MAX_CLIENTS],
                        fd_set *read_socket, char *buffer);

/**
 * Add new connected client to clients list and check if connection was
 * successful.
 *
 * @param client_socket_list: A list of ints which are the connected client
 *                            sockets.
 * @param server_socket: An int representing the server socket.
 *
 * @return An int that represents the client or -1 if the the client connection
 *fails
 **/
int new_client_connection(int client_socket_list[MAX_CLIENTS],
                          int server_socket);

/**
 * Set up the server socket with correct, non-blocking parameters.
 *
 * @return: An int storing the socket number of the server socket or -1
 *          if there is an error;
 **/
int setup_server_socket();

/**
 * Check that server socket binds properly, sends appropriate errors
 * if not.
 *
 * @param bind_status: An int that's < 0 if the bind failed.
 *
 * @return An integer representing the status of the listening process.
 *         0 : Valid binding status.
 *         1 : Error.
 **/
int check_bind_status(int bind_status);

/**
 * Check that server socket listens properly, sends appropriate errors
 * if not.
 *
 * @param listen_status: An int that's < 0 if the listen failed.
 *
 * @return An integer representing the status of the listening process.
 *         0 : Valid listening status.
 *         1 : Error.
 **/
int check_listening_status(int listen_status);

/**
 * Refresh the read and write sockets to prepare for data.
 *
 * @param read_socket: An fd_set pointer that points to the socket which the
 *                     server detected had new data.
 * @param write_socket: An fd_set pointer that points to the socket which the
 *                      server should write new data to.
 * @param server_socket: An int representing the server socket.
 * @param client_socket_list: A list of ints which are the connected client
 *                            sockets.
 **/
void refresh_sockets(fd_set *read_socket, fd_set *write_socket,
                     int server_socket, const int client_socket_list[MAX_CLIENTS]);

#endif // SERVER_H
