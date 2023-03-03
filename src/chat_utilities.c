#include "chat_utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void get_username(char* username) {
    while(1) {
        printf("Enter a username: ");
        fgets(username, USERNAME_BUFFER_SIZE + 1, stdin);
        if (strlen(username) > USERNAME_BUFFER_SIZE) {
            printf("Error: Username is over 16 characters");
            fflush(stdin);
            continue;
        } else {
            username[strcspn(username, "\n")] = 0;
            break;
        } 
    }
}

void get_timestamp(char* timestamp) {
    time_t rawtime = time ( &rawtime );
    char* timeinfo = asctime ( localtime ( &rawtime ) );
    strncpy(timestamp, timeinfo + 11, 8);  
}

int main(void) {
    char username[USERNAME_BUFFER_SIZE + 1];
    get_username(username);
    printf("%s", username);
    char timestamp[TIMESTAMP_BUFFER_SIZE + 1];
    get_timestamp(timestamp);
    printf("%s", timestamp);
    return 0;
}
