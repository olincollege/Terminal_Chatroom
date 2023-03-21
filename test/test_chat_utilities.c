#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/chat_utilities.h"

void send_stdin(const char* input) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "%s\n", input);
  (void)fclose(stdin_file);
}

// Check that an empty username gets a default name.
Test(get_username, valid_username) {
  char username[USERNAME_BUFFER_SIZE + 1];
  send_stdin("");
  get_username(username);
  cr_assert(eq(str, username, "Anon"));
}

// Check that the user's username is assigned properly to username.
Test(get_username, default_username) {
  char username[USERNAME_BUFFER_SIZE + 1];
  send_stdin("Marc");
  get_username(username);
  cr_assert(eq(str, username, "Marc"));
}

// Check that a username longer than 16 chars gets truncated.
Test(get_username, truncates_username) {
  char username[USERNAME_BUFFER_SIZE + 1];
  send_stdin("HelloMyUsernameIsOver16Characters");
  get_username(username);
  cr_assert(eq(str, username, "HelloMyUsernameI"));
}

// Check if timestamp is returned in hh:mm:ss format.
Test(get_timestamp, proper_timestamp_format) {
  char timestamp[TIMESTAMP_BUFFER_SIZE + 1];
  get_timestamp(timestamp);
  cr_assert(eq(chr, timestamp[2], ':'));
  cr_assert(eq(chr, timestamp[5], ':'));
}

// Check if create packet concatenates message meta data
// correctly.
Test(create_packet, creates_packet_message) {
  char packet[PACKET_BUFFER_SIZE] = "";
  char username[USERNAME_BUFFER_SIZE + 1] = "Mac";
  char message[PACKET_BUFFER_SIZE] = "Hi!";
  create_packet(&packet[0], &username[0], &message[0]);
  cr_assert(eq(chr, packet[0], 'M'));
  cr_assert(eq(chr, packet[1], 'a'));
  cr_assert(eq(chr, packet[2], 'c'));
  cr_assert(eq(chr, packet[3], ' '));
  cr_assert(eq(chr, packet[4], '('));
  cr_assert(eq(chr, packet[7], ':'));
  cr_assert(eq(chr, packet[10], ':'));
  cr_assert(eq(chr, packet[13], ')'));
  cr_assert(eq(chr, packet[14], ':'));
  cr_assert(eq(chr, packet[15], ' '));
  cr_assert(eq(chr, packet[16], 'H'));
  cr_assert(eq(chr, packet[17], 'i'));
  cr_assert(eq(chr, packet[18], '!'));
}
