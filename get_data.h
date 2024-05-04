/*
 * Name:       return_codes.h
 *
 * Purpose:    Header file for get_data.c.
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

#ifndef GET_DATA_H

#define GET_DATA_H

void get_date_string(const char *line, char *date_string);
void get_amount_string(const char *line, char *amount_string);
int get_month(const char *date_string, int *error_code);
int get_day(const char *date_string, int *error_code);
int get_year(const char *date_string, int *error_code);
double get_amount(const char *amount_string);

#endif