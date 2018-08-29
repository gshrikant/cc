/**
 * @file log.h
 * @brief Basic logging (not thread-safe).
 * @author Shrikant Giridhar
 */
#ifndef __CC_LOG_H__
#define __CC_LOG_H__
#include <stdarg.h>

typedef enum {
    LOG_CRITICAL,	/* Unrecoverable error. */
    LOG_ERROR,		/* Recoverable error. */
    LOG_WARN		/* Prompt for (possible) action. */,
    LOG_INFO,		/* General operating information. */
    LOG_DEBUG,		/* Debug information. */
} loglevel_t;

void log_set(loglevel_t level);
void log_printf(loglevel_t level, const char *format, ...);

#endif /* __CC_LOG_H__ */
