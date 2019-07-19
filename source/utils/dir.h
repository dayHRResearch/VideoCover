#ifndef UTILS_DIR_H
#define UTILS_DIR_H

#ifndef MAKE_DIR
#define MAKE_DIR
#include <sys/stat.h>
#include <sys/types.h>
#endif // MAKE_DIR

#ifndef REMOVE_DIR
#define REMOVE_DIR
#include <unistd.h>
#endif // REMOVE_DIR

#ifndef IO
#define IO
#include <iostream>
#endif // IO

// Create a directory if the file directory does not exist.
int checkDirExists() {
  std::string dir_name = "./images";
  if (access(dir_name.c_str(), 0) != -1)
    return 0;
  else {
    int flag = mkdir(dir_name.c_str(), 0777);

    if (flag == 0)
      return 0;
    else
      return -1;
  }
  return 0;
}

// Delete files generated during program running.
int cleanDir() {
  std::string dir_name = "./images";
  if (rmdir(dir_name.c_str()) != -1)
    return 0;
  else
    return -1;
}

#endif // UTILS_DIR_H