#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#define PORT 8080
#define MAX_CLIENTS 5

int newClientConnection(int (*client_socket_list)[MAX_CLIENTS], int sockfd) {
  int client = accept(sockfd, NULL, NULL);

  if (client < 0) {
    perror("Client Connection Failed");
  } else {
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (*client_socket_list[i] == 0) {
        *client_socket_list[i] = client;
        perror("Client Succeed");
        return client;
      }
    }
  }
  return 0;
}

int main() {
  fd_set current_sockets;
  int client_socket_list[MAX_CLIENTS] = {
      0,
  };
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
  } else {
    perror("Socket Creation Succeeded");
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int bind_status =
      bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));

  if (bind_status < 0) {
    perror("Unable to Bind Socket");
    exit(EXIT_FAILURE);
  }
  int listen_status = listen(sockfd, MAX_CLIENTS);

  if (listen_status < 0) {
    perror("Unable to Listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    FD_ZERO(&current_sockets);
    FD_SET(sockfd, &current_sockets);
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (client_socket_list[i] > 0) {
        FD_SET(client_socket_list[i], &current_sockets);
      }
    }
    int select_status = select(MAX_CLIENTS, &current_sockets, NULL, NULL, NULL);
    if (select_status < 0) {
      perror("Error With Selecting");
    } else if (select_status != 0) {
      if (FD_ISSET(sockfd, &current_sockets)) {
        newClientConnection(&client_socket_list, sockfd);
      } else {
      }
    }
  }
  return 0;
}
