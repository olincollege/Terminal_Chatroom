#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/server.h"

void redirect_all_std(void) {
  cr_redirect_stdout();
  cr_redirect_stderr();
}

// Check that a valid socket binding doesn't raise an error.
Test(check_bind_status, valid_connection) {
  int bind_status = 1;
  cr_assert(eq(int, check_bind_status(bind_status), 0));
}

// Check that a valid socket listening status doesn't raise an error.
Test(check_listening_status, valid_connection) {
  int listen_status = 1;
  cr_assert(eq(int, check_listening_status(listen_status), 0));
}

// Check that a socket listening error is raised.
Test(check_bind_status, listening_error, .init = redirect_all_std) {
  int bind_status = -1;
  check_bind_status(bind_status);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Unable to Bind Socket\n");
}

// Check that a bind status error is raised.
Test(check_listening_status, binding_error, .init = redirect_all_std) {
  int listen_status = -1;
  check_listening_status(listen_status);
  (void)fflush(stdout);
  cr_assert_stdout_eq_str("Unable to Listen\n");
}
