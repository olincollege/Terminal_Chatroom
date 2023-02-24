#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
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

  bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));

  listen(sockfd, 5);

  int client;

  client = accept(sockfd, NULL, NULL);

  char server_message[256] = "Hoho";
  send(client, server_message, sizeof(server_message), 0);

  return 0;
}
