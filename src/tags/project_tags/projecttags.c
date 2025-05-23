#include "projecttags.h"

void project_build_tag(const char* dir, struct dirent* entry) {
  if (strcmp(entry->d_name, "ninja.build.tag") != 0) {
    return;
  }

  char* filename = strfmt("%s/%s", dir, entry->d_name);
  FILE* file = fopen(filename, "r");

  if (!file) {
    perror(filename);
    return;
  }

  free(filename);

  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  char* buffer = malloc(size + 1);
  fread(buffer, size, 1, file);

  char* buildfilename = strfmt("%s/build.ninja", dir);
  FILE* buildfile = fopen(buildfilename, "w");
  if (!buildfile) {
    perror(buildfilename);
    return;
  }
  BUILD_FILES = fl_append(BUILD_FILES, buildfilename);
  free(buildfilename);

  fprintf(buildfile, "\n%s\n", buffer);
  free(buffer);

  fclose(file);
  fclose(buildfile);
}
