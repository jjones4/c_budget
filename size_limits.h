/*
 * Name:       size_limits.h
 *
 * Purpose:    Macros defining size limts for various parts of the data. This
 *             file contains macros that are intended to be shared by multiple
 *             files that need this information.
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

#ifndef SIZE_LIMITS_H

#define SIZE_LIMITS_H

/*
 * Macros defining data size limits intended to be shared among multiple parts
 * of the program.
 */
#define LINE_BUFFER_SIZE 512

/*
 * I subtract this padding when I'm too lazy to worry about exactly what is
 * going on at the end of strings, such as with calls to fgets. I read a little
 * more data than intended and then cut off some of the data at the end. Then I
 * manually control the handling of the remaining data.
 */
#define PADDING 16

/*
 * All "lengths" include one extra for the null character.
 */
#define MONTH_LENGTH 3
#define DAY_LENGTH 3
#define YEAR_LENGTH 5

#define DATE_LENGTH 11
#define AMOUNT_LENGTH_MAX 10
#define AMOUNT_LENGTH_MIN 4

#define START_YEAR 2018
#define END_YEAR 2099
#define NUMBER_OF_MONTHS (12 * (END_YEAR - START_YEAR + 1))
#define NUMBER_OF_YEARS (END_YEAR - START_YEAR + 1)

#endif