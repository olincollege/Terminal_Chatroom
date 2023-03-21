#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/server.h"

void redirect_all_std(void) {
  cr_redirect_stdout();
  cr_redirect_stderr();
}

// Check that a valid socket connection doesn't raise an error.
Test(check_socket_bind_listen, valid_connection) {
  int bind_status = 1;
  int listen_status = 1;
  cr_assert(eq(int, check_socket_bind_listen(bind_status, listen_status), 0));
}

// Check that a socket listening error is raised.
Test(check_socket_bind_listen, listening_error, .init = redirect_all_std) {
  int bind_status = 1;
  int listen_status = -1;
  check_socket_bind_listen(bind_status, listen_status);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Unable to Listen\n");
}

// Check that a bind status error is raised.
Test(check_socket_bind_listen, binding_error, .init = redirect_all_std) {
  int bind_status = -1;
  int listen_status = 1;
  check_socket_bind_listen(bind_status, listen_status);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Unable to Bind Socket\n");
}
