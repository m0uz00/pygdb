#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/parse_file.h"

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

  int lines = count_lines(buffer);
  char* file = string_to_array(buffer, lines);

  free(buffer);

  return "kys";
}

int count_lines(char* buffer){
  char* split_buffer;
  split_buffer = strtok(buffer, "\n");

  int lines = 0;

  while(split_buffer != NULL){
    split_buffer = strtok(NULL, "\n");
    lines++;
  }

  return lines;
}

char* string_to_array(char* buffer, int lines){
  char* split_buffer;
  char* file[lines];

  split_buffer = strtok(buffer, "\n");

  int i = 0;
  while(split_buffer != NULL){
    file[i] = split_buffer;
    split_buffer = strtok(NULL, "\n");
    i++;
  }

  return *file;
}
