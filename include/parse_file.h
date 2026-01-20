#pragma once

#include <stdio.h>

#include "utils.h"

#ifndef PARSE_FILE_H
#define PARSE_FILE_H

program* parse(FILE* path);

line* find_first_line(list* lines);

list* find_functions(list* lines);

#endif
