#pragma once
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct file_list_t file_list_t;
struct file_list_t {
  file_list_t* prev;
  char* name;
};

extern file_list_t* OBJS;
extern file_list_t* BUILD_FILES;

char* strfmt(const char* fmt, ...);
file_list_t* fl_append(file_list_t* files, const char* str);
void fl_iter(file_list_t* files, void (*func)(char*));
void fl_write(file_list_t* files, const char* fmt, ...);
void fl_free(file_list_t* files);
