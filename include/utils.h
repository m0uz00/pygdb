#pragma once

#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

struct line{
  int line_num;
  char* line_text;
} typedef line;

struct list_item{
  line* line;
  struct list_item* prev;
  struct list_item* next;
} typedef list_item;

struct list{
  list_item* head;
  list_item* tail;
  int len;
} typedef list;

struct program {
  list* funcs;
  list* vars;
  line* entry;
  list* lines;
} typedef program;

list* append(list* list, list_item* item);

char** string_to_arr(char* buffer, int lines, char* delim);

int count_lines(char* buffer);

char** split_string(char* buffer, char* delim);

list* arr_to_list(char** arr, int len);

list_item* ith_line(int i);

#endif
