#include "tags/tag.h"
#include <dirent.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void traverse(const char* dir,
              void (*func)(const char*, struct dirent*)) {
  struct dirent* entry;
  DIR* dp = opendir(dir);
  if (dp == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dp)) != NULL) {
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") != 0 &&
          strcmp(entry->d_name, "..") != 0) {
        char* path = strfmt("%s/%s", dir, entry->d_name);
        traverse(path, func);
        free(path);
      }
    } else {
      func(dir, entry);
    }
  }

  closedir(dp);
}

#include "tags/c_tags/ctags.h"
#include "tags/project_tags/projecttags.h"

int main() {
  traverse(".", project_build_tag);

  if (!BUILD_FILES) {
    fprintf(stderr, "no build files found\n");
    exit(1);
  }

  traverse(".", c_object_tag);
  traverse(".", c_exec_tag);

  fl_free(OBJS);
  fl_free(BUILD_FILES);
  return 0;
}
