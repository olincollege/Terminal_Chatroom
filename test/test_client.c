#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/client.h"

// Check that a bad socket is rejected.
Test(hello, invalid_socket) {
  // int sockfd = -1;
  cr_assert(eq(1, 0));
  // cr_assert(eq(int, check_socket_creation(sockfd), 0));
}

// // Check that a bad socket is rejected.
// Test(check_socket_creation, hi) {
//   int sockfd = 1;
//   cr_assert(eq(int, sockfd, 0));
//   // cr_assert(eq(int, check_socket_creation(sockfd), 0));
// }

