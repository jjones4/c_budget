/*
 * Name:       validate_budget_line.h
 *
 * Purpose:    Macros and function definitions for validating a line from the
 *             budget file.
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

#ifndef VALIDATE_BUDGET_LINE_H

#define VALIDATE_BUDGET_LINE_H

/*
 * Macros and functions used for validating a line from the budget file.
 */
int validate_budget_line(char **line, int line_number);

#endif