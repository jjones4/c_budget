/*
 * Name:       boolean.h
 *
 * Purpose:    Setting up typedef for Bool and macros for true/false.
 *
 *             c_budget is c89 compliant, so it uses typedef and macros for
 *             boolean instead of <stdbool.h>.
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

#ifndef BOOLEAN_H

#define BOOLEAN_H

#define TRUE 1
#define FALSE 0

typedef int Bool;

#endif