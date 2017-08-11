#include "log.h"

int main(int argv, char** argc) {
    log_set_enable(1);
    log_set_level(LOG_DEBUG);
    log_debug("Hello world");
    log_info("Hello world");
    log_warn("Hello world");
    log_error("Hello world");
    return 0;
}
