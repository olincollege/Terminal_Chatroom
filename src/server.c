#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#define PORT 8080
#define MAX_CLIENTS 5
#define MAX_MESSAGE_LENGTH 1024

void broadcastData(int senderIdx, int client_socket_list[MAX_CLIENTS],
                   char buffer[MAX_MESSAGE_LENGTH]) {
  char bufferEmpty[MAX_MESSAGE_LENGTH];
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (i != senderIdx && client_socket_list[i] != 0) {
      write(client_socket_list[i], buffer, strlen(buffer));
    }
  }
}

void handleData(int client_socket_list[MAX_CLIENTS], fd_set *read_socket,
                fd_set *write_socket) {
  char buffer[MAX_MESSAGE_LENGTH];
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (client_socket_list[i] != 0) {
      if (FD_ISSET(client_socket_list[i], read_socket)) {
        int bytes_received =
            recv(client_socket_list[i], buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
          buffer[bytes_received] = '\0';
          printf("%s \n", buffer);
          broadcastData(i, client_socket_list, buffer);
        } else if (bytes_received == 0) {
          printf("Client %d disconnected\n", client_socket_list[i]);
          close(client_socket_list[i]);
          client_socket_list[i] = 0;
        } else {
          perror("Receiving Failure");
        }
      }
    }
  }
}

int newClientConnection(int client_socket_list[MAX_CLIENTS],
                        int server_socket) {
  int client = accept(server_socket, NULL, NULL);
  if (client < 0) {
    perror("Client Connection Failed");
  } else {
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (client_socket_list[i] == 0) {
        client_socket_list[i] = client;
        perror("Client Connection");
        printf("New Client Joined \n");
        return client;
      }
    }
  }
  return 0;
}

int main() {
  char buffer[MAX_MESSAGE_LENGTH];
  struct timeval tv;

  fd_set read_socket, write_socket;
  int client_socket_list[MAX_CLIENTS] = {
      0,
  };
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
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int bind_status = bind(server_socket, (struct sockaddr *)&server_address,
                         sizeof(server_address));

  if (bind_status < 0) {
    perror("Unable to Bind Socket");
    exit(EXIT_FAILURE);
  }
  int listen_status = listen(server_socket, MAX_CLIENTS);

  if (listen_status < 0) {
    perror("Unable to Listen");
    exit(EXIT_FAILURE);
  }
  while (1) {
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
    int select_status =
        select(FD_SETSIZE, &read_socket, &write_socket, NULL, &tv);
    if (select_status < 0) {
      perror("Error With Selecting");
    } else if (select_status != 0) {
      if (FD_ISSET(server_socket, &read_socket)) {
        newClientConnection(client_socket_list, server_socket);
      } else {
        handleData(client_socket_list, &read_socket, &write_socket);
      }
    }
  }
  return 0;
}
