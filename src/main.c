#include <stdlib.h>
#include <stdio.h>

#include "../include/parse_file.h"
#include "../include/run.h"

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("You need to provide a file path!\n");
    return 1;
  } 

  char* path = argv[1];

  printf("Attempting to open: %s\n\n", path);

  FILE* fp = fopen(path, "r+");
  if(!fp){
    perror("File cant be opened");
    return 1;
  }

  program* program = malloc(sizeof(program));
  parse(fp);

  run_file(program);

  return 0;
}
