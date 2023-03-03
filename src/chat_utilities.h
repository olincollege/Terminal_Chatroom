#pragma once

/**
 * Returns the current time and formats it in hh:mm:ss format.
 *
 * @return A string representing the current time in hh:mm:ss format.
 */
void get_timestamp(char*);

// Set the maximum input size that shout can read.
enum { 
    USERNAME_BUFFER_SIZE = 16,
    TIMESTAMP_BUFFER_SIZE = 8
    };

/**
 * Asks the user for their username and returns it.
 *
 * @param username A username.
 * @return A string representing the user's username.
 */
void get_username(char*);
