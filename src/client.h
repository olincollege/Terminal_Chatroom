#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum { PORT = 8080 } Constants;
/**
 * Checks if the socket was created successfully, throws an error if not.
 *
 * @param sockfd An integer representing the socket the client is connected to.
 * @return
 */
int check_socket_creation(int sockfd);

/**
 * Checks if a connection was made to the server successfully, throws an
 * error if not.
 *
 * @param connection_status An integer representing the connection status.
 */
int check_connection_status(int connection_status);

/**
 * Reads the stdin buffer and clears the line the user types after enter is
 * pressed.
 *
 * Since the server sends back a prettified version of the message with the
 * user's username and timestamp, the user's original message can be deleted
 * from the user's terminal so it can be replaced with the server's response.
 *
 * @param buffer The stdin buffer which represents the user's message.
 */
void read_buffer(char *buffer);

/**
 * Writes a packet to the server's and client's shared socket.
 *
 * The packet is generated on the user's side as a string containing
 * the user's username, timestamp of the message, and the message itself.
 * This is sent to the server using the write_to_server function.
 *
 * @param sockfd An integer representing the socket the client is connected to.
 * @param packet A string containing the username, timestamp of message, and
 *               message.
 * @param read_fd An fd_set struct used to clear the file descriptor from the
 * socket. *************** What
 */
void write_to_server(int sockfd, char *packet, fd_set read_fd);

/**
 * Reads incoming data from the server and prints it to the user's terminal.
 *
 * The packet received contains the status of if the retreival failed or if the
 * connection to the server was lost. If none of these are true, the received
 * packet is used to add a null character to the end of the received string
 * buffer. The buffer contains a string representing the user's username,
 * timestamp of the message, and message. This buffer is then printed to the
 * user's terminal.
 *
 * @param packet_received An integer representing the status of the received
 * packet or the length of the buffer.
 * @param buffer The buffer that contains the packet data from the server.
 */
int read_from_server(int packet_received, char *buffer);

#endif
