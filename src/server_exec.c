#include "server.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

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
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    refresh_sockets(&read_socket, &write_socket, server_socket,
                    client_socket_list);
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
        check_read_sockets(client_socket_list, &read_socket, buffer);
      }
    }
  }
  return 0;
}
