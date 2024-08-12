#include "liblog.h"

static void test_function(void) { log_debug("Reached the desired point..."); }

int main(void) {
  log_info("Testing formats: %d", 123);
  test_function();
  log_warn("Got negative value");
  log_error("Unexpected value: %p", NULL);
  log_fatal("Failed to allocate enough memory");

  return 0;
}
