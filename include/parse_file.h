#pragma once

#include <stdio.h>

#ifndef PARSE_FILE_H
#define PARSE_FILE_H

char* parse(FILE* path);

int count_lines(char* buffer);

char* string_to_array(char* buffer, int lines);

#endif
