#include "../include/dir.h"

// Create a directory if the file directory does not exist.
int check_dir_exists(const char *dir_name) {
  if (access(dir_name, 0) != -1)
    mkdir(dir_name, 755);
  else
    return -1;
  return 0;
}

// Delete files generated during program running.
int clean_dir(const char *dir_name) {
  if (rmdir(dir_name) != -1)
    ;
  else
    return -1;
  return 0;
}