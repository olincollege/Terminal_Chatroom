#include "chat_utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void get_username(char* username) {
    printf("Enter a username: ");
    fgets(username, USERNAME_BUFFER_SIZE + 1, stdin);
    username[strcspn(username, "\n")] = 0;
}

void get_timestamp(char* timestamp) {
    time_t rawtime = time ( &rawtime );
    char* timeinfo = asctime ( localtime ( &rawtime ) );
    strncpy(timestamp, timeinfo + 11, 8);  
}

void create_packet(char* packet, char* username, char* timestamp) {
    strcat(packet, username);
    strcat(packet, " (");
    strcat(packet, timestamp);
    strcat(packet, ")");
}

int main(void) {
    char username[USERNAME_BUFFER_SIZE + 1];
    get_username(username);
    char timestamp[TIMESTAMP_BUFFER_SIZE + 1];
    get_timestamp(timestamp);
    char packet[50] = "";
    create_packet(packet, username, timestamp);
    printf("%s", packet);
    return 0;
}
