#include "../../include/dir.h"

// Create a directory if the file directory does not exist.
int __mkdir__(const char *dir_name) {
  if (mkdir(dir_name, 0777) != -1)
    return 0;
  else
    return -1;
}

// Delete files generated during program running.
int __rmdir__(const char *dir) {
  char cur_dir[] = ".";
  char up_dir[] = "..";
  char dir_name[128];
  DIR *dirp;
  struct dirent *dp;
  struct stat dir_stat;

  if (0 != access(dir, F_OK)) {
    return 0;
  }

  if (0 > stat(dir, &dir_stat)) {
    perror("get directory stat error");
    return -1;
  }

  if (S_ISREG(dir_stat.st_mode)) {
    remove(dir);
  } else if (S_ISDIR(dir_stat.st_mode)) {
    dirp = opendir(dir);
    while ((dp = readdir(dirp)) != NULL) {
      if ((0 == strcmp(cur_dir, dp->d_name)) ||
          (0 == strcmp(up_dir, dp->d_name))) {
        continue;
      }

      sprintf(dir_name, "%s/%s", dir, dp->d_name);
      __rmdir__(dir_name);
    }
    closedir(dirp);

    rmdir(dir);
  } else {
    perror("unknow file type!");
  }
  return 0;
}
