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
  } else {
    perror("Connection Succeeded");
  }

  char server_response[256];
  recv(sockfd, &server_response, sizeof(server_response), 0);
  printf(server_response);
  return 0;
}
