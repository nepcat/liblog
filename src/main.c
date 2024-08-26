#include "liblog.h"

static void test_function(void) { log_debug("Reached the desired point..."); }
static void test_var(int var) { log_trace("test_var: %d", var); }

int main(void) {
  test_var(1337);
  log_info("Testing formats: %d", 123);
  test_function();
  log_warn("Got negative value");
  log_error("Unexpected value: %p", NULL);
  log_fatal("Failed to allocate enough memory");

  return 0;
}
