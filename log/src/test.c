#include "log.h"
#define UNUSED(expr) do { (void)(expr); } while(0)

int main(int argv, char** argc) {
    UNUSED(argv);
    UNUSED(argc);
    log_set_enable(1);
    log_set_level(LOG_DEBUG);
    log_debug("Hello World");
    log_info("Hello World");
    log_warn("Hello World");
    log_error("Hello World");
    return 0;
}
