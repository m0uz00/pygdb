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

  free(buffer);

  return "kys";
}

int find_first_line(list* lines){
  regex_t regex;
  char* exp = "^(?!def|\\t| |#|\\d)\\w+";



  return 0;
};
