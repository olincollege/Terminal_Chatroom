#include "chat_utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void get_username(char* username) {
    printf("Enter a username: ");
    (void) fgets(username, USERNAME_BUFFER_SIZE + 1, stdin);
    if (username[0] == '\n') {
        strncpy(username, "Anon", USERNAME_BUFFER_SIZE + 1);
    } else {
        username[strcspn(username, "\n")] = 0;
    }
}

void get_timestamp(char* timestamp) {
    time_t rawtime = time ( &rawtime );
    char* timeinfo = asctime ( localtime ( &rawtime ) );
    strncpy(timestamp, timeinfo + 11, 8);  
}

void create_packet(char* packet, char* username, char* message) {
    strncpy(packet, "", sizeof(*packet));
    strcat(packet, username);
    strcat(packet, " (");
    char timestamp[TIMESTAMP_BUFFER_SIZE + 1];
    get_timestamp(timestamp);
    strcat(packet, timestamp);
    strcat(packet, "): ");
    strcat(packet, message);
}
