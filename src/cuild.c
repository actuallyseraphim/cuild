#include "tags/tag.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

void traverse(const char *dir, void (*func)(const char*, struct dirent*)) {
  struct dirent *entry;
  DIR *dp = opendir(dir);
  if (dp == NULL) {
    perror("opendir");
    return;
  }
  
  while ((entry = readdir(dp)) != NULL) {
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
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

#include "tags/project_tags/projecttags.h"
#include "tags/c_tags/ctags.h"

int main() {
  traverse(".", project_build_tag);
  if (BUILD_FILE == 0) {
    fprintf(stderr, "no build file");
    exit(1);
  }
  
  traverse(".", c_object_tag);
  traverse(".", c_exec_tag);
  
  fclose(BUILD_FILE);
  struct obj_list_t *node = OBJS;
  while ( node != 0) {
    free(node->name);
    struct obj_list_t *t = node;
    node = node->prev;
    free(t);
  }
  return 0;
}
