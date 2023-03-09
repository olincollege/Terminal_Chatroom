#include <arpa/inet.h>
#include "chat_utilities.c"
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080

void check_socket_creation(int sockfd) {
  if (sockfd < 0) {
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
  } else {
    perror("Socket Creation Succeeded");
  }
}

void check_connection_status(int connection_status) {
  if (connection_status != 0) {
    perror("Connection Failed");
    exit(EXIT_FAILURE);
  } else {
    perror("Connection Succeeded");
  }
}

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // check_socket_creation(sockfd);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect(sockfd, (struct sockaddr *)&server_address,
                                  sizeof(server_address));

  // check_connection_status(connection_status);

  char username[USERNAME_BUFFER_SIZE + 1];
  get_username(username);

  char packet[100];
  char message[7] = "Hello!";
  create_packet(packet, username, message);
  printf("%s", packet);

  char buffer[1024];
  fd_set read_fd, write_fd;
  FD_ZERO(&read_fd);
  FD_ZERO(&write_fd);
  FD_SET(sockfd, &read_fd);
  FD_SET(sockfd, &write_fd);
  struct timeval tv;

  while (1) {
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    fd_set temp_read = read_fd;
    fd_set temp_write = write_fd;
    int select_status = select(sockfd + 1, &temp_read, &temp_write, NULL, &tv);
    if (select_status < 0) {
      perror("Error With Selecting");
    }

    if (FD_ISSET(sockfd, &temp_write)) {
      fgets(buffer, sizeof(buffer), stdin);
      if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
      }
      if (write(sockfd, buffer, strlen(buffer)) == -1) {
        perror("Write Failed");
        exit(EXIT_FAILURE);
      } else {
        FD_CLR(sockfd, &write_fd);
      }
    }
    if (FD_ISSET(sockfd, &temp_read)) {
      int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
      if (bytes_received == -1) {
        perror("Receive Failed");
        exit(EXIT_FAILURE);
      } else if (bytes_received == 0) {
        printf("Connection Closed\n");
        break;
      } else {
        buffer[bytes_received] = '\0';
        printf("%s\n", buffer);
      }
      FD_SET(sockfd, &read_fd);
    }

    if (FD_ISSET(STDIN_FILENO, &temp_read)) {
      fgets(buffer, sizeof(buffer), stdin);
      if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
      }
      if (write(sockfd, buffer, strlen(buffer)) == -1) {
        perror("Write Failed");
        exit(EXIT_FAILURE);
      } else {
        FD_CLR(STDIN_FILENO, &read_fd);
      }
    }

    FD_SET(sockfd, &read_fd);
    FD_SET(STDIN_FILENO, &read_fd);
  }

  close(sockfd);
  return 0;
}
