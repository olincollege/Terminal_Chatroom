#include "server.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

// Function to send messages to all clients
void broadcast_data(int client_socket_list[MAX_CLIENTS],
                    char buffer[MAX_MESSAGE_LENGTH]) {
  // loop through all connected clients
  for (int current_client = 0; current_client < MAX_CLIENTS; current_client++) {
    if (client_socket_list[current_client] != 0) {
      write(client_socket_list[current_client], buffer, strlen(buffer));
    }
  }
}

void handle_receive(int client_socket_list[MAX_CLIENTS],
                    char buffer[MAX_MESSAGE_LENGTH], int current_client) {
  // number of bytes received; 0=client disconnect, <0=error, >0=message
  int bytes_received = (int)recv(client_socket_list[current_client], buffer,
                                (MAX_MESSAGE_LENGTH * (size_t) 4), 0);
  // if client is sending a message
  if (bytes_received > 0) {
    buffer[bytes_received] = '\0';
    printf("%s \n", buffer);
    broadcast_data(client_socket_list, buffer);
    // if a client has disconnected
  } else if (bytes_received == 0) {
    printf("Client %d disconnected\n", client_socket_list[current_client]);
    close(client_socket_list[current_client]);
    client_socket_list[current_client] = 0;
    // if data read indicates an error
  } else {
    perror("Receiving Failure");
  }
}

void check_read_sockets(int client_socket_list[MAX_CLIENTS],
                        fd_set *read_socket, char buffer[MAX_MESSAGE_LENGTH]) {
  // loop through all connected clients
  for (int i = 0; i < MAX_CLIENTS; i++) {
    // if client exists and data is ready to be read from client socket
    if (client_socket_list[i] != 0) {
      if (FD_ISSET(client_socket_list[i], read_socket)) {
        // function to handle the data read from the socket
        handle_receive(client_socket_list, buffer, i);
      }
    }
  }
}

int new_client_connection(int client_socket_list[MAX_CLIENTS],
                          int server_socket) {
  // variable that stores status of connected client
  // warning suggests accept4 which does not compile with C99
  int client = accept(server_socket, NULL, NULL);
  if (client < 0) {
    perror("Client Connection Failed");
  } else {
    // add new client to first open slot in client list
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (client_socket_list[i] == 0) {
        client_socket_list[i] = client;
        perror("Client Connection");
        printf("New Client Joined \n");
        return client;
      }
    }
    return -1;
  }
  return -1;
}

int setup_server_socket() {
  // socket status for server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    printf("Socket Creation Failed");
    return -1;
  }
  printf("Socket Creation Succeeded");
  if (fcntl(server_socket, F_SETFL, 
    (fcntl(server_socket, F_GETFL) == 1) || (O_NONBLOCK == 1)) < 0) {
    printf("Server is Blocking");
    return -1;
  }
  return server_socket;
}

int check_bind_status(int bind_status) {
  if (bind_status < 0) {
    printf("Unable to Bind Socket\n");
    return 1;
  }
  return 0;
}

int check_listening_status(int listen_status) {
  if (listen_status < 0) {
    printf("Unable to Listen\n");
    return 1;
  }
  return 0;
}

void refresh_sockets(fd_set *read_socket, fd_set *write_socket,
                     int server_socket, const int client_socket_list[MAX_CLIENTS]) {
  FD_ZERO(read_socket);
  FD_SET(server_socket, read_socket);
  FD_ZERO(write_socket);
  FD_SET(server_socket, write_socket);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (client_socket_list[i] != 0) {
      FD_SET(client_socket_list[i], read_socket);
      FD_SET(client_socket_list[i], write_socket);
    }
  }
}
