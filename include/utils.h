#pragma once

#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

enum objectType {
  function = 0,
  variable = 1,
} typedef objectType;

struct list_item{
  int value;
  struct list_item* prev;
  struct list_item* next;
} typedef list_item;

struct list{
  list_item* item;
  list_item* head;
  list_item* tail;
} typedef list;

struct var{
  int line_num;
} typedef var;

list* append(list* list, int value);

char* string_to_arr(char* buffer, int lines, char* delim);

int count_lines(char* buffer, char* delim);

char* split_string(char* buffer, char* delim);

#endif
