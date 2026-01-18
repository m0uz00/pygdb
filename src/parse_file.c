#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>
#include <string.h>

#include "../include/parse_file.h"
#include "../include/utils.h"

#define OVECCOUNT 30

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
    printf("First runnable line: %s\n", first_line->line_text);
  } else {
    printf("No matching line found.\n");
  }

  list* functions = find_functions(lines);

  free(buffer);
  return "kys";
}

line* find_first_line(list* lines){
  if (lines == NULL || lines->head == NULL) {
      return NULL;
  }
  
  pcre *re;
  char* pattern = "^(?!def|\\t| |#|\\d)\\w+(.*)?";
  
  list_item* current = lines->head;
  line* result = NULL;
  const char* error;
  int erroroffset;
  int ovector[OVECCOUNT];
  int rc;
  
  if (re == NULL){
    perror("Error compiling expression");
  }

  while (current!=NULL){
    line* current_line = current->line;

    char* subject = current_line->line_text;
    int subject_len = (int)strlen(subject);
    re = pcre_compile(pattern, 0, &error, &erroroffset, NULL);
    if (current_line != NULL && current_line->line_text != NULL){        
      rc = pcre_exec(re, NULL, subject, subject_len, 0, 0, ovector, OVECCOUNT);
      if (rc > 0){
        result = current_line;
        break;
      }
    }
    current = current->next;
  }
  pcre_free(re);
  return result;
};


list* find_functions(list* lines){
  if (lines == NULL || lines->head == NULL){
    return NULL;
  }

  list* functions;
  functions->len = 0;
  
  pcre *re;
  char* pattern = "^def *\\w+";

  list_item* current = lines->head;
  const char* error;
  int erroroffset;
  int ovector[OVECCOUNT];
  int rc;

  if (re == NULL){
    perror("Error compiling expression");
  }

  while (current!=NULL){
    line* current_line = current->line;

    char* subject = current_line->line_text;
    int subject_len = (int)strlen(subject);
    re = pcre_compile(pattern, 0, &error, &erroroffset, NULL);
    if (current_line != NULL && current_line->line_text != NULL){        
      rc = pcre_exec(re, NULL, subject, subject_len, 0, 0, ovector, OVECCOUNT);
      if (rc > 0){
        functions = append(functions, current);
        printf("found function, %s\n", current->line->line_text);
      }
    }
    current = current->next;
  }
  pcre_free(re);
  return functions;
}
