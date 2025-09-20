#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define ERROR(message, ...)                                \
    fprintf(stderr, "%s:%i: error: ", __FILE__, __LINE__); \
    fprintf(stderr, message, ##__VA_ARGS__)

#endif
