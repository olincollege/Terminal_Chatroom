#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080

int main() {
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

  int connection_status = connect(sockfd, (struct sockaddr *)&server_address,
                                  sizeof(server_address));

  if (connection_status != 0) {
    perror("Connection Failed");
    exit(EXIT_FAILURE);
  } else {
    perror("Connection Succeeded");
  }

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (write(sockfd, buffer, strlen(buffer)) == -1) {
      perror("Write Failed");
      exit(EXIT_FAILURE);
    }
    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
      perror("Receive Failed");
      exit(EXIT_FAILURE);
    } else if (bytes_received == 0) {
      printf("Connection Closed by Peer\n");
      break;
    } else {
      buffer[bytes_received] = '\0';
      printf("%s", buffer);
    }
  }

  close(sockfd);
  return 0;
}
