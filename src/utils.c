#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

char** string_to_arr(char* buffer, int lines, char* delim){
  char** text = malloc(sizeof(char*) * lines); 
  if (!text) return NULL;

  char* split_buffer = strtok(buffer, delim);
  int i = 0;
  while(split_buffer != NULL && i < lines) {
    text[i] = split_buffer; 
    split_buffer = strtok(NULL, delim);
    i++;
  }

  return text;
}

int count_lines(char* buffer){
  int lines = 0;
  char* ptr = buffer;
  while (*ptr) {
    if (*ptr == '\n') {
      if (*(ptr + 1) != '\n' && *(ptr + 1) != '\0') {
         lines++;
      }
    }
      ptr++;
  }
  return lines + 1;
}

char** split_string(char* buffer, char* delim){
  int lines = count_lines(buffer);

  return string_to_arr(buffer, lines, delim);
}

list* append(list* list, list_item* item){
  if(list->len == 0){
    item->prev = NULL;
    item->next = NULL;

    list->head = item;
    list->tail = item;
    list->len++;

    return list;
  }

  list->tail->next = item;
  item->prev = list->tail;
  list->tail = item;
  list->len++;

  return list;
}

list* arr_to_list(char** arr, int len){
  list* new_list = calloc(1, sizeof(list));
    if(!new_list) return NULL;

    for(int i = 0; i < len; i++) {
        line* current_line = malloc(sizeof(line));
        current_line->line_num = i;
        current_line->line_text = arr[i]; 

        list_item* new_element = calloc(1, sizeof(list_item));
        new_element->line = current_line;
        append(new_list, new_element);
    }
    return new_list;
}

list_item* ith_line(int i){
}
