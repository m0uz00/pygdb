#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

char* string_to_arr(char* buffer, int lines, char* delim){
  char* split_buffer;
  char* text[lines];

  split_buffer = strtok(buffer, delim);

  int i = 0;
  while(split_buffer != NULL){
    text[i] = split_buffer;
    split_buffer = strtok(NULL, delim);
    i++;
  }

  return *text;
}

int count_lines(char* buffer, char* delim){
  char* split_buffer;
  split_buffer = strtok(buffer, delim);

  int lines = 0;

  while(split_buffer != NULL){
    split_buffer = strtok(NULL, delim);
    lines++;
  }

  return lines;
}

char* split_string(char* buffer, char* delim){
  int lines = count_lines(buffer, delim);

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

list* arr_to_list(char* arr, int len){
  list* new_list = malloc(sizeof(new_list));
  if(!new_list){
    perror("malloc error");
  }
  for(int i = 0; i < len; i++){
    line* current_line = malloc(sizeof(line));
    if(!current_line){
      perror("malloc error");
    }
    current_line->line_num = i;
    current_line->line_text = &arr[i];

    list_item* new_element = malloc(sizeof(list_item));
    if(!new_element){
      perror("malloc error");
    }
    new_element->line = current_line;
    new_element->prev = NULL;
    new_element->next = NULL;
    

    new_list = append(new_list, new_element);

    free(current_line);
    free(new_element);
  }
  
  return new_list;
}
