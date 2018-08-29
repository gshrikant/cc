/**
 * @file lex.c
 * @brief Scan character input stream and generate tokens.
 * @author Shrikant Giridhar
 */
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <cc/lex.h>

