#include "projecttags.h"

void project_build_tag(const char *dir, struct dirent *entry) {
  if (strcmp(entry->d_name, "ninja.build.tag") != 0) {
    return;
  }
  
  char *filename = strfmt("%s/%s", dir, entry->d_name);
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s!\n", filename);
    return;
  }
  free(filename);

  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  char *buffer = malloc(size+1);
  fread(buffer, size, 1, file);

  if (BUILD_FILE) {
    fclose(BUILD_FILE);
  }
  
  BUILD_FILE = fopen(BUILD_FILE_NAME, "w");
  fprintf(BUILD_FILE, "\n%s\n", buffer);
  free(buffer);
  
  fclose(file);
}
