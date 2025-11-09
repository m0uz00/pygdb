#pragma once

#include <stdio.h>

#include "utils.h"

#ifndef PARSE_FILE_H
#define PARSE_FILE_H

char* parse(FILE* path);

line* find_first_line(list* lines);

#endif
