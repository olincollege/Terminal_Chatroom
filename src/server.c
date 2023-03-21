#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

// Define globals
#define PORT 8080
#define MAX_CLIENTS 5
#define MAX_MESSAGE_LENGTH 1024

// Function to send messages to all clients
void broadcast_data(int senderIdx, int client_socket_list[MAX_CLIENTS],
                   char buffer[MAX_MESSAGE_LENGTH]) {
  // loop through all connected clients
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (client_socket_list[i] != 0) {
      write(client_socket_list[i], buffer, strlen(buffer));
    }
  }
}

void handle_receive(int client_socket_list[MAX_CLIENTS], fd_set *read_socket, char buffer[MAX_MESSAGE_LENGTH], int current_client) {
  // number of bytes received; 0=client disconnect, <0=error, >0=message
  int bytes_received = recv(client_socket_list[current_client], buffer, sizeof(buffer), 0);
  // if client is sending a message
  if (bytes_received > 0) {
    buffer[bytes_received] = '\0';
    printf("%s \n", buffer);
    broadcast_data(current_client, client_socket_list, buffer);
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

void check_read_sockets(int client_socket_list[MAX_CLIENTS], fd_set *read_socket,
                fd_set *write_socket) {
  char buffer[MAX_MESSAGE_LENGTH];
  // loop through all connected clients
  for (int i = 0; i < MAX_CLIENTS; i++) {
    // if client exists and data is ready to be read from client socket
    if (client_socket_list[i] != 0) {
      if (FD_ISSET(client_socket_list[i], read_socket)) {
        // function to handle the data read from the socket
        handle_receive(client_socket_list, &read_socket, buffer, i);
      }
    }
  }
}

void new_client_connection(int client_socket_list[MAX_CLIENTS],
                        int server_socket) {
  // variable that stores status of connected client
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
  }
}

int setup_server_socket() {
  // socket status for server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
  } else {
    perror("Socket Creation Succeeded");
  }
  if (fcntl(server_socket, F_SETFL,
            fcntl(server_socket, F_GETFL) | O_NONBLOCK) < 0) {
    perror("Server is Blocking");
    exit(EXIT_FAILURE);
  }
  return server_socket;
}

void check_socket_bind_listen(int bind_status, int listen_status) {
  if (bind_status < 0) {
    perror("Unable to Bind Socket");
    exit(EXIT_FAILURE);
  }
  if (listen_status < 0) {
    perror("Unable to Listen");
    exit(EXIT_FAILURE);
  }
}

void refresh_sockets(fd_set read_socket, fd_set write_socket,
                    int server_socket, int client_socket_list[MAX_CLIENTS],
                    struct timeval tv) {
  tv.tv_sec = 0;
  tv.tv_usec = 10000;
  FD_ZERO(&read_socket);
  FD_SET(server_socket, &read_socket);
  FD_ZERO(&write_socket);
  FD_SET(server_socket, &write_socket);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (client_socket_list[i] != 0) {
      FD_SET(client_socket_list[i], &read_socket);
      FD_SET(client_socket_list[i], &write_socket);
    }
  }
}

int main() {
  // Initialize vars
  char buffer[MAX_MESSAGE_LENGTH];
  struct timeval tv;

  // Create socket variables
  fd_set read_socket, write_socket;
  int client_socket_list[MAX_CLIENTS] = {0};
  int server_socket = setup_server_socket();

  // Create server address struct
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind and listen server socket
  int bind_status = bind(server_socket, (struct sockaddr *)&server_address,
                         sizeof(server_address));
  int listen_status = listen(server_socket, MAX_CLIENTS);
  check_socket_bind_listen(bind_status, listen_status);

  // Main loop
  while (1) {
    // variable that tracks if read or write sockets have pending actions
    int select_status =
        select(FD_SETSIZE, &read_socket, &write_socket, NULL, &tv);
    if (select_status < 0) {
      perror("Error With Selecting");
    } else if (select_status != 0) {
      if (FD_ISSET(server_socket, &read_socket)) {
        // When server socket has connection request, new client connection
        new_client_connection(client_socket_list, server_socket);
      } else {
        // check client sockets for messages or connection changes
        check_read_sockets(client_socket_list, &read_socket, &write_socket);
      }
    }
  }
  return 0;
}
