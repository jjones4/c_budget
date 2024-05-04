/*
 * Name:       get_data.c
 *
 * Purpose:    Functions for fullfilling requests for data, such as getting the
 *             date or amount from the budget transaction line.
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

#include <stdio.h>
#include <stdlib.h>
#include "get_data.h"
#include "return_codes.h"
#include "size_limits.h"

int get_month(const char *date_string, int *error_code) {

   int month = 0;
   char *month_string = NULL;
   char *month_string_ptr;
   char *temp_ptr;

   month_string = malloc(MONTH_LENGTH * sizeof(char));
   month_string_ptr = month_string;

   if(month_string == NULL) {
      *error_code = MEMORY_ERROR;
      return 0;
   }

   while(*date_string != '/') {
      *month_string = *date_string;
      ++month_string;
      ++date_string;
   }

   *month_string = '\0';

   month = strtol(month_string_ptr, &temp_ptr, 10);

   free(month_string_ptr);

   return month;
}

int get_day(const char *date_string, int *error_code) {

   int day = 0;
   char *day_string = NULL;
   char *day_string_ptr;
   char *temp_ptr;

   day_string = malloc(DAY_LENGTH * sizeof(char));
   day_string_ptr = day_string;

   if(day_string == NULL) {
      *error_code = MEMORY_ERROR;
      return 0;
   }

   /*
    * Skip to the first character after the first forward slash.
    */
   while(*date_string != '/') {
      ++date_string;
   }

   ++date_string;

   while(*date_string != '/') {
      *day_string = *date_string;
      ++day_string;
      ++date_string;
   }

   *day_string = '\0';

   day = strtol(day_string_ptr, &temp_ptr, 10);

   free(day_string_ptr);
      
   return day;
}

int get_year(const char *date_string, int *error_code) {

   int year = 0;
   char *year_string = NULL;
   char *year_string_ptr;
   char *temp_ptr;

   year_string = malloc(YEAR_LENGTH * sizeof(char));
   year_string_ptr = year_string;

   if(year_string == NULL) {
      *error_code = MEMORY_ERROR;
      return 0;
   }

   /*
    * Skip to the first character after the first forward slash.
    */
   while(*date_string != '/') {
      ++date_string;
   }

   ++date_string;

   /*
    * Skip to the first character after the second forward slash.
    */
   while(*date_string != '/') {
      ++date_string;
   }

   ++date_string;

   while(*date_string) {
      *year_string = *date_string;
      ++year_string;
      ++date_string;
   }

   *year_string = '\0';

   year = strtol(year_string_ptr, &temp_ptr, 10);

   free(year_string_ptr);

   return year;
}

double get_amount(const char *amount_string) {

   double amount = 0.00;
   char *ptr;
   
   amount = strtod(amount_string, &ptr);

   return amount;
}

void get_amount_string(const char *line, char *amount_string) {

   /*
    * Skip to the character directly after the first pipe.
    */
   while(*line != '|') {
      ++line;
   }

   ++line;

   /*
    * Start filling the amount string.
    */
   while(*line != '|') {
      *amount_string = *line;
      ++amount_string;
      ++line;
   }

   *amount_string = '\0';
}

void get_date_string(const char *line, char *date_string) {

   while(*line != '|') {
      *date_string = *line;
      ++date_string;
      ++line;
   }

   *date_string = '\0';
}
