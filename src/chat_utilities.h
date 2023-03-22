#pragma once

// Set the maximum input size that shout can read.
enum { 
    USERNAME_BUFFER_SIZE = 16,
    TIMESTAMP_BUFFER_SIZE = 8,
    PACKET_BUFFER_SIZE = 1024,
    TIMESTAMP_LENGTH = 11
};

/**
 * Gets the current time and formats it in hh:mm:ss format and saves it in
 * a variable called timestamp.
 *
 * @param timestamp A character pointer that will point to the formatted
 *                  timestamp.
 */
void get_timestamp(char* timestamp);

/**
 * Asks the user for their username through stdin and saves it in a variable
 * called username.
 *
 * @param username A character pointer that will point to the username.
 */
void get_username(char* username);

/**
 * Concatenates the username, timestamp, and user message into a single
 * string that is later sent to the server. This concatenated string is
 * saved to a variable called packet.
 *
 * @param packet A character pointer that will point to the concatenated
 *               packet.
 * @param username A character pointer that points to the user's username.
 * @param message A character pointer that points to the user's message.
 */
void create_packet(char* packet, char* username, char* message);
