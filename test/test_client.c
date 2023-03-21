#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/client.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Check that a valid socket isn't rejected.
Test(check_socket_creation, valid_socket) {
  int sockfd = 1;
  cr_assert(eq(int, check_socket_creation(sockfd), 0));
}

// Check that an invalid socket is rejected.
Test(check_socket_creation, invalid_socket) {
  int sockfd = -1;
  cr_assert(eq(int, check_socket_creation(sockfd), 1));
}

// Check that an error message shows when a bad socket is rejected.
Test(check_socket_creation, error_message, .init = redirect_all_std) {
  check_connection_status(-1);
  (void) fflush(stdout);
  cr_assert_stdout_eq_str("Socket Creation Failed\n");
}

// Check that a valid connection status isn't rejected.
Test(check_connection_status, valid_connection) {
  int sockfd = 1;
  cr_assert(eq(int, check_connection_status(sockfd), 0));
}

// Check that an invalid connection status is rejected.
Test(check_connection_status, invalid_connection) {
  int sockfd = -1;
  cr_assert(eq(int, check_connection_status(sockfd), 1));
}

// Check that an error message shows when a bad socket is rejected.
Test(check_connection_status, error_message, .init = redirect_all_std) {
  check_socket_creation(-1);
  (void) fflush(stdout);
  cr_assert_stdout_eq_str("Socket Creation Failed\n");
}

// // Check that a bad socket is rejected.
// Test(check_socket_creation, hi) {
//   int sockfd = 1;
//   cr_assert(eq(int, sockfd, 0));
//   // cr_assert(eq(int, check_socket_creation(sockfd), 0));
// }
