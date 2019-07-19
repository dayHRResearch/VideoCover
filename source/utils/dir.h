#ifndef UTILS_DIR_H
#define UTILS_DIR_H

#ifndef MAKE_DIR
#define MAKE_DIR
#include <sys/stat.h>
#include <sys/types.h>
#endif  // MAKE_DIR

#ifndef DIR_OP
#define DIR_OP
#include <dirent.h>
#endif

#ifndef REMOVE_DIR
#define REMOVE_DIR
#include <unistd.h>
#endif  // REMOVE_DIR

#ifndef IO
#define IO
#include <iostream>
#endif  // IO

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

using namespace std;

int checkDirExists();
int cleanDir();

// Create a directory if the file directory does not exist.
int checkDirExists() {
  std::string dir_name = "./images";
  if (access(dir_name.c_str(), 0) != -1) {
    cleanDir();
    if (mkdir(dir_name.c_str(), 0777))
      return 0;
    else
      return -1;

  } else {
    if (mkdir(dir_name.c_str(), 0777))
      return 0;
    else
      return -1;
  }
}

// Delete files generated during program running.
int cleanDir() {
  std::string dir_name = "./images";
  if (rmdir(dir_name.c_str()) != -1)
    return 0;
  else
    return -1;
}

#endif  // UTILS_DIR_H