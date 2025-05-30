#include "ctags.h"

void c_object_tag(const char* dir, struct dirent* entry) {
  if (strcmp(entry->d_name, "c.object.tag") != 0) {
    return;
  }
  char* filename = strfmt("%s/%s", dir, entry->d_name);
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s!\n", filename);
  }
  free(filename);

  char output[1024];
  char input[1024];
  fscanf(file, "%s%s", output, input);
  fclose(file);
  fl_write(BUILD_FILES, "build obj/%s: cc %s/%s\n", output, dir,
           input);
  OBJS = fl_append(OBJS, output);
}

void __print_all_to_build_file(char* file) {
  fl_write(BUILD_FILES, " obj/%s", file);
}

void c_exec_tag(const char* dir, struct dirent* entry) {
  if (strcmp(entry->d_name, "c.exec.tag") != 0) {
    return;
  }
  char* filename = strfmt("%s/%s", dir, entry->d_name);
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s!\n", filename);
  }
  free(filename);

  char output[1024];
  char input[1024];
  fscanf(file, "%s%s", output, input);
  fclose(file);
  fl_write(BUILD_FILES, "build %s: link %s/%s", output, dir,
           input);
  fl_iter(OBJS, __print_all_to_build_file);
  fl_write(BUILD_FILES, "\ndefault %s\n", output);
}
