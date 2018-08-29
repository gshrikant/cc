/**
 * @file log.c
 * @brief Internal logging facilities.
 * @author Shrikant Giridhar
 */
#include <stdio.h>
#include <cc/log.h>

static loglevel_t current_level = LOG_WARN;

/**
 * @brief Set current log level.
 * @param level Target log level.
 */
void
log_set(loglevel_t level)
{
    current_level = level;
}

/**
 * @brief Formatted print to log.
 * @param level Requested log level.
 * @param format Format string.
 */
void
log_printf(loglevel_t level, const char *format, ...)
{
    if (level < current_level)
	return;

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
