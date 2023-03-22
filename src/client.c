#include "chat_utilities.h"
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

int check_socket_creation(int sockfd) {
  if (sockfd < 0) {
    printf("Socket Creation Failed\n");
    return 1;
  }
  printf("Socket Creation Succeeded\n");
  return 0;
}

int check_connection_status(int connection_status) {
  if (connection_status != 0) {
    printf("Connection Failed\n");
    return 1;
  }
  printf("Connection Succeeded\n");
  return 0;
}

void read_buffer(char *buffer) {
  // This string clears what the user just typed to prevent two messages
  // on the user's terminal.
  printf("\033[A");
  if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
  }
}

void write_to_server(int sockfd, char *packet, fd_set read_fd) {
  if (write(sockfd, packet, strlen(packet)) == -1) {
    printf("Write Failed\n");
  } else {
    FD_CLR(STDIN_FILENO, &read_fd);
  }
}

int read_from_server(int packet_received, char *buffer) {
  if (packet_received == -1) {
    printf("Receive Failed\n");
    return 0;
  }
  if (packet_received == 0) {
    printf("Connection Closed\n");
    return 1;
  }
  // Set a terminating character to the end of the buffer that
  // we received.
  buffer[packet_received] = '\0';
  printf("%s\n", buffer);
  return 0;
}
