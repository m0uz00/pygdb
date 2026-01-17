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

  char* buffer = malloc(length + 1); 
  if (buffer) {
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
  }
  fclose(f);

  int line_count = count_lines(buffer);
    
  char** lines_array = (char**)split_string(buffer, "\n");
  if (!lines_array) return "error";

    list* lines = arr_to_list(lines_array, line_count);
    line* first_line = find_first_line(lines);

    if (first_line != NULL) {
        printf("%s\n", first_line->line_text);
    } else {
        printf("No matching line found.\n");
    }

  free(buffer);
  return "kys";
}

line* find_first_line(list* lines){
  if (lines == NULL || lines->head == NULL) {
      return NULL;
  }

  regex_t regex;
  const char* exp = "^(?!def|\\t| |#|\\d)\\w+";
  int reti;

  reti = regcomp(&regex, exp, 0);
  
  list_item* current = lines->head;
  line* result = NULL;

  while (current!=NULL){
    line* current_line = current->line;

    if (current_line != NULL && current_line->line_text != NULL){
      reti = regexec(&regex, current_line->line_text,0 ,NULL, 0);
      if (!reti){
        result = current_line;
        break;
      }
    }
    current = current->next;
  }
  regfree(&regex);

  return result;
};
