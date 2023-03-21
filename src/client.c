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

void read_buffer(char* buffer) {
  printf("\033[A");
  if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
    buffer[strlen(buffer) - 1] = '\0';
  }
}

void write_to_server(int sockfd, char* packet, fd_set read_fd) {
  if (write(sockfd, packet, strlen(packet)) == -1) {
    printf("Write Failed\n");
  } else {
    FD_CLR(STDIN_FILENO, &read_fd);
  }
}

int read_from_server(int packet_received, char* buffer) {
  if (packet_received == -1) {
    printf("Receive Failed\n");
  } else if (packet_received == 0) {
    printf("Connection Closed\n");
    return 1;
  } else {
    buffer[packet_received] = '\0';
    printf("%s\n", buffer);
    return 0;
  }
}


// int main() {
//   // int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//   int sockfd = -1;
//   if (check_socket_creation(sockfd)) {
//     return 0;
//   };

//   struct sockaddr_in server_address;
//   server_address.sin_family = AF_INET;
//   server_address.sin_port = htons(PORT);
//   server_address.sin_addr.s_addr = INADDR_ANY;

//   int connection_status = connect(sockfd, (struct sockaddr *)&server_address,
//                                   sizeof(server_address));

//   check_connection_status(connection_status);

//   char username[USERNAME_BUFFER_SIZE + 1];
//   get_username(username);

//   char buffer[1024];
//   char packet[1024];
//   fd_set read_fd, write_fd;
//   FD_ZERO(&read_fd);
//   FD_ZERO(&write_fd);
//   FD_SET(sockfd, &read_fd);
//   FD_SET(sockfd, &write_fd);
//   struct timeval tv;

//   while (1) {
//     tv.tv_sec = 0;
//     tv.tv_usec = 100000;
//     fd_set temp_read = read_fd;
//     fd_set temp_write = write_fd;
//     int select_status = select(sockfd + 1, &temp_read, &temp_write, NULL, &tv);
//     if (select_status < 0) {
//       perror("Error With Selecting");
//     }

//     if (FD_ISSET(sockfd, &temp_read)) {
//       int packet_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
//       if (read_from_server(packet_received, buffer)) {
//         break;
//       };
//       FD_SET(sockfd, &read_fd);
//     }

//     if (FD_ISSET(STDIN_FILENO, &temp_read)) {
//       fgets(buffer, sizeof(buffer), stdin);
//       read_buffer(buffer);
//       create_packet(packet, username, buffer);
//       write_to_server(sockfd, packet, read_fd);
//     }

//     FD_SET(sockfd, &read_fd);
//     FD_SET(STDIN_FILENO, &read_fd);
//   }

//   // close(sockfd);
//   return 0;
// }
