/**
 * Copyright 2019 DayHR Authors. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ==============================================================================
 */

/**
 * @ author: Changyu Liu
 * @ last modifly time: 2019.7.25
 */

#ifndef SMILE_INCLUDE_DOWNLOAD_H
#define SMILE_INCLUDE_DOWNLOAD_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif  // STDIO_H

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif  // TIME_H

#ifndef ARPA_INET_H
#define ARPA_INET_H
#include <arpa/inet.h>
#endif  // ARPA_INET_H

#ifndef ERRNO_H
#define ERRNO_H
#include <errno.h>
#endif  // ERRNO_H

#ifndef FCNTL_H
#define FCNTL_H
#include <fcntl.h>
#endif  // FCNTL_H

#ifndef NETDB_H
#define NETDB_H
#include <netdb.h>
#endif  // NETDB_H

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif  // STDIO_H

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif  // STRING_H

#ifndef SYS_SOCKET_H
#define SYS_SOCKET_H
#include <sys/socket.h>
#endif  // SYS_SOCKET_H

#ifndef SYS_TYPES_H
#define SYS_TYPES_H
#include <sys/types.h>
#endif  // SYS_TYPES_H

#ifndef UNISTD_H
#define UNISTD_H
#include <unistd.h>
#endif  // UNISTD_H

#define HOST_NAME_LEN 256
#define URI_MAX_LEN 2048
#define RECV_BUF 8192
#define RCV_SND_TIMEOUT (10 * 1000)

typedef struct {
  int sock;  // Socket Communicating with Server
  FILE *in;  // Sock descriptor to file pointer, easy to read and write
  char host_name[HOST_NAME_LEN];
  int port;
  char url[URI_MAX_LEN];
  char buffer[RECV_BUF];
  int status_code;
  int chunked_flag;
  int len;
  char location[URI_MAX_LEN];
  char *save_path;
  FILE *save_file;
  int recv_data_len;
  time_t start_recv_time;
  time_t end_recv_time;
} http_t;

#define MSG_DEBUG 0x01
#define MSG_INFO 0x02
#define MSG_ERROR 0x04

#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define HTTP_OK 200
#define HTTP_REDIRECT 302
#define HTTP_NOT_FOUND 404

#ifndef PRINT_LEVEL
#define PRINT_LEVEL
static int print_level = /*MSG_DEBUG |*/ MSG_INFO | MSG_ERROR;
#endif  // PRINT_LEVEL

#endif  // SMILE_INCLUDE_DOWNLOAD_H