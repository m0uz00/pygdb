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

  printf("%s\n", buffer);

  return "kys";
}
