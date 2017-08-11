#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

#define log_error(...) log_print(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_print(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_print(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_print(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

void log_set_enable(int enable);
void log_set_level(int level);
void log_print(int level, const char *file, int line, const char *fmt, ...);

#endif
