#include "tag.h"
#include <stdarg.h>
#include <stdio.h>

file_list_t* BUILD_FILES;
file_list_t* OBJS = 0;

char* strfmt(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int size = vsnprintf(NULL, 0, fmt, args) + 1;
  va_end(args);

  if (size <= 0)
    return NULL;

  char* buf = malloc(size);
  if (!buf)
    return NULL;

  va_start(args, fmt);
  vsnprintf(buf, size, fmt, args);
  va_end(args);

  return buf;
}

file_list_t* fl_append(file_list_t* files, const char* str) {
  file_list_t* t = files;
  files = malloc(sizeof(*files));
  *files = (file_list_t){.prev = t, .name = strdup(str)};
  return files;
}

void fl_iter(file_list_t* files, void (*func)(char*)) {
  for (file_list_t* node = files; node != 0;
       node = node->prev) {
    func(node->name);
  }
}

char* __FL_WRITE_TEXT;
size_t __FL_WRITE_TEXT_SIZE;
void __fl_write_single(char* filename) {
  FILE* file = fopen(filename, "a");
  if (!file) {
    return;
  }
  fwrite(__FL_WRITE_TEXT, __FL_WRITE_TEXT_SIZE, 1, file);
  fclose(file);
}

void fl_write(file_list_t* files, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int size = vsnprintf(NULL, 0, fmt, args) + 1;
  va_end(args);

  if (size <= 0)
    return;

  char* buf = malloc(size);
  if (!buf)
    return;

  va_start(args, fmt);
  vsnprintf(buf, size, fmt, args);
  va_end(args);

  __FL_WRITE_TEXT_SIZE = size - 1;
  __FL_WRITE_TEXT = buf;
  fl_iter(files, __fl_write_single);
}

void fl_free(file_list_t* files) {
  file_list_t* node = files;
  while (node != 0) {
    free(node->name);
    file_list_t* t = node;
    node = node->prev;
    free(t);
  }
}
