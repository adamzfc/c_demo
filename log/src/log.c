#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "log.h"

/**
 * LOG struct
 */
static struct {
    int level;
    int enable;
} LOG;

/**
 * log levle name
 */
static const char *level_names[] = {
    "DEBUG", "INFO", "WARN", "ERROR"
};

/**
 * log level color
 */
static const char *level_colors[] = {
    "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"
};

void log_set_level(int level) {
    LOG.level = level;
}

void log_set_enable(int enable) {
    LOG.enable = enable;
}

void log_print(int level, const char *file, int line, const char *fmt, ...) {
    if (level < LOG.level) {
        return;
    }
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    if (LOG.enable) {
        va_list args;
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
        fprintf(stderr, "%s %s%-5s\x1b[0m \x1b[97m%s:%d:\x1b[0m ",
                buf, level_colors[level], level_names[level], file, line);
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
    }
    
}
