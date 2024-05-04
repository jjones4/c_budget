/*
 * Name:       program_init.h
 *
 * Purpose:    Macro definitions and directives for program_init.c.
 *
 * Author:     jjones4
 *
 * Copyright (c) 2024 Jerad Jones
 *
 * This file is part of c_budget. c_budget may be freely distributed under the
 * MIT license. For all details and documentation, see:
 *
 *             https://github.com/jjones4/c_budget
 */

#ifndef PROGRAM_INIT_H

#define PROGRAM_INIT_H

#include <stdio.h>
#include "boolean.h"

/*
 * c_budget assumes DEFAULT_DATA_FILE is the name of the budget data file if
 * user does not provide user-defined file name as a command line argument.
 */
#define DEFAULT_DATA_FILE "budget_data.txt"
#define FILE_NAME_LENGTH 100
#define MAX_ARG_COUNT 2
#define MIN_ARG_COUNT 1

int program_init(int argument_count, char **argument_vector,
   char **data_file_name);

#endif