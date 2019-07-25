#ifndef INCLUDE_LOG_H
#define INCLUDE_LOG_H

#include "download.h"
/**
 * print error.
 * example: "[MSG_ERROR][parser_URL(101)]:url invaild"
 * @ author: Changyu Liu
 * @ last modifly time: 2019.7.25
 */
#define lprintf(level, format, argv...)                                       \
  do {                                                                        \
    if (level & print_level)                                                  \
      printf("[%s][%s(%d)]:" format, #level, __FUNCTION__, __LINE__, ##argv); \
  } while (0)

#endif  // INCLUDE_LOG_H