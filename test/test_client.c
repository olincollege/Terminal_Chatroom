#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/client.h"

void redirect_all_std(void) {
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
Test(check_socket_creation, socket_error_message, .init = redirect_all_std) {
  check_socket_creation(-1);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Socket Creation Failed\n");
}

// Check that a valid connection status isn't rejected.
Test(check_connection_status, valid_connection) {
  int connection_status = 0;
  cr_assert(eq(int, check_connection_status(connection_status), 0));
}

// Check that an invalid connection status is rejected.
Test(check_connection_status, invalid_connection) {
  int connection_status = 1;
  cr_assert(eq(int, check_connection_status(connection_status), 1));
}

// Check that an error message shows when a bad connection is rejected.
Test(check_connection_status, connection_error_message,
     .init = redirect_all_std) {
  check_connection_status(1);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Connection Failed\n");
}

// Check that read buffer correctly reads user input.
Test(read_buffer, read_buffer_reads_user_input) {
  char *buffer = "Hello everyone!";
  read_buffer(buffer);
  cr_assert(eq(str, buffer, "Hello everyone!\0"));
}

// Check that read buffer correctly erases what the user's inital
// unformatted message.
Test(read_buffer, clears_unformatted_message, .init = redirect_all_std) {
  char *buffer = "Hello everyone!";
  read_buffer(buffer);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("\033[A");
}

// Check that an invalid packet is rejected with a proper error messsage.
Test(read_from_server, invalid_packet, .init = redirect_all_std) {
  char *buffer = "Hello everyone!";
  int packet_received = -1;
  cr_assert(eq(int, read_from_server(packet_received, buffer), 0));
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Receive Failed\n");
}

// Check that a packet indicating a closed connection returns correctly and
// prints a connection closed message.
Test(read_from_server, closed_connection, .init = redirect_all_std) {
  char *buffer = "Hello everyone!";
  int packet_received = 0;
  cr_assert(eq(int, read_from_server(packet_received, buffer), 1));
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Connection Closed\n");
}

// Check that read from server prints the buffer from the packet.
Test(read_from_server, prints_packet_message, .init = redirect_all_std) {
  char buffer[] = "Hello!";
  int packet_received = sizeof(buffer);
  cr_assert(eq(int, read_from_server(packet_received, &buffer[0]), 0));
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Hello!\n");
}
