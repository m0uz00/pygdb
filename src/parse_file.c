#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "../include/parse_file.h"
#include "../include/utils.h"

char* parse(FILE* f){

  long length;

  fseek(f, 0, SEEK_END);
  length = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* buffer = malloc(length);
  if(buffer){
    fread(buffer, 1, length, f);
  }
  fclose(f);

  int line_count = count_lines(buffer, "\n");
  char* file = split_string(buffer, "\n");

  list* lines = arr_to_list(file, line_count);

  line* first_line = find_first_line(lines);

  printf("%s", first_line->line_text);


  free(buffer);

  return "kys";
}

line* find_first_line(list* lines){
  regex_t regex;
  char* exp = "^(?!def|\\t| |#|\\d)\\w+";
  int reti;

  reti = regcomp(&regex, exp, 0);
  list_item* current = lines->head;
  for(int i = 0; i < lines->len; i++){
    line* current_line = malloc(sizeof(line));
    current_line = current->line;
    if(current_line->line_text != NULL){
     
      reti = regexec(&regex , current_line->line_text, 0, NULL, 0);
      if(!reti){
        return current_line;
      }
    }
    current = current->next;
  }
  regfree(&regex);

  return NULL;
};
