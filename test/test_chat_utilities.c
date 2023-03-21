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
  cr_assert(eq(str, timestamp[2], ":"));
}

// // Check that a bad socket is rejected.
// Test(check_socket_creation, hi) {
//   int sockfd = 1;
//   cr_assert(eq(int, sockfd, 0));
//   // cr_assert(eq(int, check_socket_creation(sockfd), 0));
// }
