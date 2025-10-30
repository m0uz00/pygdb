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

  char* file = split_string(buffer, "\n");

  free(buffer);

  return "kys";
}

int find_first_line(char* file){
  
  return 0;
};
