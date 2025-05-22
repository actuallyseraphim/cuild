#include "tag.h"
#include <stdarg.h>

const char *BUILD_FILE_NAME = "build.ninja";
FILE *BUILD_FILE;

struct obj_list_t *OBJS = 0;

char* strfmt(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int size = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  if (size < 0) return NULL;
  char* buf = malloc(size + 1);
  if (!buf) return NULL;
  va_start(args, fmt);
  vsnprintf(buf, size + 1, fmt, args);
  va_end(args);
  return buf;
}

