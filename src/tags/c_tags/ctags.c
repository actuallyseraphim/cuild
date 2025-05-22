#include "ctags.h"

void c_object_tag(const char *dir, struct dirent *entry) {
  if (strcmp(entry->d_name, "c.object.tag") != 0) {
    return;
  }
  char *filename = strfmt("%s/%s", dir, entry->d_name);
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s!\n", filename);
  }
  free(filename);

  
  char output[1024];
  char input[1024];
  fscanf(file, "%s%s", output, input);
  fclose(file);
  fprintf(BUILD_FILE, "build obj/%s: cc %s/%s\n", output, dir, input);

  struct obj_list_t *t = OBJS;
  OBJS = malloc(sizeof(*OBJS));
  *OBJS = (struct obj_list_t){.prev = t, .name = strdup(output)};
}

void c_exec_tag(const char *dir, struct dirent *entry) {
  if (strcmp(entry->d_name, "c.exec.tag") != 0) {
    return;
  }
  char *filename = strfmt("%s/%s", dir, entry->d_name);
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s!\n", filename);
  }
  free(filename);

  char output[1024];
  char input[1024];
  fscanf(file, "%s%s", output, input);
  fclose(file);
  
  fprintf(BUILD_FILE, "build %s: link %s/%s", output, dir, input);
  for (struct obj_list_t *node = OBJS; node != 0; node = node->prev) {
    fprintf(BUILD_FILE, " obj/%s", node->name);
  }
  fprintf(BUILD_FILE, "\ndefault  %s\n", output);
}
