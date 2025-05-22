#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <dirent.h>

extern const char *BUILD_FILE_NAME;
extern FILE *BUILD_FILE;

struct obj_list_t {
  struct obj_list_t *prev;
  char* name;
};

extern struct obj_list_t *OBJS;

char *strfmt(const char *fmt, ...);
