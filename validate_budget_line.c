/*
 * Name:       validate_budget_line.c
 *
 * Purpose:    Perform all required checks to ensure a given line of data from
 *             the budget file contains a valid date, amount, and description.
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
#include <string.h>
#include "boolean.h"
#include "size_limits.h"
#include "return_codes.h"
#include "validate_budget_line.h"
#include "get_data.h"

#define CHARS_BEFORE_DECIMAL_POINT 6
#define CHARS_AFTER_DECIMAL_POINT 2

Bool is_valid_line_termination(const char *line, int line_length);
Bool is_valid_line_format(const char *line);
Bool is_valid_date_format(const char *date_string);
Bool is_valid_amount_format(const char *amount_string);
Bool is_valid_numerical_char_placement_date_string(const char *date_string);
Bool is_valid_numerical_char_placement_amount_string(const char *amount_string);
Bool is_valid_month(const int month);
Bool is_valid_day(const int month, const int day, const int year);

int validate_budget_line(char **line, int line_number) {

   int month = 0; int day = 0; int year = 0;
   int error_code = 0;
   double amount = 0.00;
   char *date_string = NULL;
   char *amount_string = NULL;

   if(is_valid_line_termination(*line, LINE_BUFFER_SIZE) == FALSE) {
      printf("\nLine %d contains too much data.\n",
         line_number + 1);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_line_format(*line) == FALSE) {

      printf("\nIncorrect placement of a pipe character was detected on line");
      printf(" number %d\n", line_number + 1);

      return DATA_VALIDATION_ERROR;
   }

   date_string = malloc(DATE_LENGTH * sizeof(char));
   amount_string = malloc(AMOUNT_LENGTH_MAX * sizeof(char));
   
   if(date_string == NULL || amount_string == NULL) {
      printf("\nThere was an error getting the required memory.\n");

      return MEMORY_ERROR;
   }

   get_date_string(*line, date_string);
   get_amount_string(*line, amount_string);

   if(is_valid_date_format(date_string) == FALSE) {

      printf("\nIncorrect placement of a slash in the date was detected on");
      printf(" line number %d\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_amount_format(amount_string) == FALSE) {

      printf("\nIncorrect format for the amount was detected on line number");
      printf(" %d\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_numerical_char_placement_date_string(date_string) == FALSE) {

      printf("\nA non-numerical characters was found where a numerical");
      printf(" character was expected in the date on line number %d.\n",
         line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_numerical_char_placement_amount_string(amount_string)
      == FALSE) {

      printf("\nA non-numerical characters was found where a numerical");
      printf(" character was expected in the amount on line number %d.\n",
         line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   month = get_month(date_string, &error_code);

   if(error_code == MEMORY_ERROR) {
      printf("\nThere was an error getting the required memory.\n");

      free(date_string);
      free(amount_string);

      return MEMORY_ERROR;
   }
   if(month == 0) {
      printf("There was an error converting the month to an integer on line");
      printf(" number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   day = get_day(date_string, &error_code);

   if(error_code == MEMORY_ERROR) {
      printf("\nThere was an error getting the required memory.\n");

      free(date_string);
      free(amount_string);

      return MEMORY_ERROR;
   }
   if(day == 0) {
      printf("There was an error converting the day to an integer on line");
      printf(" number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   year = get_year(date_string, &error_code);

   if(error_code == MEMORY_ERROR) {
      printf("\nThere was an error getting the required memory.\n");

      free(date_string);
      free(amount_string);

      return MEMORY_ERROR;
   }
   if(year == 0) {
      printf("There was an error converting the year to an integer on line");
      printf(" number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   amount = get_amount(amount_string);

   if(amount == 0.00) {
      printf("There was an error converting the amount to an integer on line");
      printf(" number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_month(month) == FALSE) {
      printf("Invalid data was found for the month in the transaction date");
      printf(" on line number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   if(is_valid_day(month, day, year) == FALSE) {
      printf("Invalid data was found for the day in the transaction date");
      printf(" on line number %d.\n", line_number + 1);

      free(date_string);
      free(amount_string);

      return DATA_VALIDATION_ERROR;
   }

   free(date_string);
   free(amount_string);

   return 0;
}

/*
 * Simply check that the days in the month are between 1 and the highest number
 * of days found in that month (also taking into account leap years).
 */
Bool is_valid_day(const int month, const int day, const int year) {
   /*
    * Months with 31 days
    */
   if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
      || month == 10 || month == 12) {
      
      if (day < 1 || day > 31) {
         return FALSE;
      }
   }

   /*
    * Months with 30 days
    */
   if (month == 4 || month == 6 || month == 9 || month == 11) {
      if (day < 1 || day > 30) {
         return FALSE;
      }
   }

   /*
    * February is a special case (28 or 29 days depending on the year)
    */
   if (month == 2) {
      /*
       * If leap year, we can have 29 days in February
       */
      if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
         if (day < 1 || day > 29) {
            return FALSE;
         }
      }
      else {
         if (day < 1 || day > 28) {
            return FALSE;
         }
      }
   }

   return TRUE;
}

/*
 * Simply check that the month is between 1 and 12, inclusive.
 */
Bool is_valid_month(const int month) {
   if(month < 1 || month > 12) {
      return FALSE;
   }
   else {
      return TRUE;
   }
}

/*
 * Simply check for numerical characters where they are expected in the amount.
 * We have to check each character (one by one) because inputs like " 2" or
 * "1a" are accepted as valid in our amount by strtol. We don't want this.
 */
Bool is_valid_numerical_char_placement_amount_string(const char *amount_string) {

   long int result = 0;
   char *temp_string = NULL;
   char *temp_ptr;

   temp_string = malloc(2 * sizeof(char));
   *++temp_string = '\0';
   --temp_string;

   while(*amount_string) {
      if(*amount_string == '-' || *amount_string == '.'
         || *amount_string == '0') {

         ++amount_string;
         continue;
      }

      *temp_string = *amount_string;

      result = strtol(temp_string, &temp_ptr, 10);

      if(result == 0) {
         return FALSE;
      }
      
      ++amount_string;
   }

   free(temp_string);

   return TRUE;
}


/*
 * Simply check for numerical characters where they are expected in the date.
 * We have to check each character (one by one) because inputs like " 2" or
 * "1a" are accepted as valid months, days, or years in our date by strtol. We
 * don't want this.
 */
Bool is_valid_numerical_char_placement_date_string(const char *date_string) {

   long int result = 0;
   char *temp_string = NULL;
   char *temp_ptr;

   temp_string = malloc(2 * sizeof(char));
   *++temp_string = '\0';
   --temp_string;

   while(*date_string) {
      if(*date_string == '/' || *date_string == '0') {
         ++date_string;
         continue;
      }

      *temp_string = *date_string;

      result = strtol(temp_string, &temp_ptr, 10);

      if(result == 0) {
         return FALSE;
      }
      
      ++date_string;
   }

   free(temp_string);

   return TRUE;
}

/*
 * Simply check for the following sequence of characters:
 *    1. One minus sign or no minus signs.
 *    2. At least 1 character and up to 5 characters before the decimal point.
 *    3. One decimal point.
 *    4. Exactly two characters after the decimal point (and no more decimal
 *       points within those two characters).
 *
 * Important note: this function ONLY checks for the correct placement of the
 * minus sign and the decimal point. It does NOT validate if the remaining
 * characters are numbers. That will be handled later.
 */
Bool is_valid_amount_format(const char *amount_string) {

   int count = 0;
   int amount_before_decimal_length = 0;

   /*
    * Set the maximin length for the amount to one less character if there is
    * not a negative sign. This prevents us from having too large of a number
    * like 999999.00 when there is no negative sign to take the place of the
    * first character.
    *
    * Skip the minus sign if present.
    */
   if(*amount_string == '-') {
      amount_before_decimal_length = CHARS_BEFORE_DECIMAL_POINT;
      ++amount_string;
   }
   else {
      amount_before_decimal_length = CHARS_BEFORE_DECIMAL_POINT - 1;
   }

   /*
    * Ensure first character (or first character after minus sign, if
    * applicable) is not a decimal point. We are enforcing that there must be
    * at least one character before the decimal (such as 0.00).
    */
   if(*amount_string == '.') {
      return FALSE;
   }

   /*
    * Skip all non-decimal characters.
    */
   while(count < amount_before_decimal_length) {
      if(*amount_string == '.') {
         break;
      }

      count++;
      ++amount_string;
   }
   
   /*
    * If we haven't found our decimal point yet, this is an error.
    */
   if(*amount_string != '.') {
      return FALSE;
   }

   ++amount_string;
   count = 0;

   /*
    * If we find our decimal point, we will not allow there to be another one,
    * and we will not allow there to be more than 2 characters after the
    * decimal.
    */
   while(*amount_string) {
      if(*amount_string == '.') {
         return FALSE;
      }

      if(count > CHARS_AFTER_DECIMAL_POINT - 1) {
         return FALSE;
      }

      count++;
      ++amount_string;
   }
   
   /*
    * Make sure we don't have too few characters before the decimal point.
    */
   if(count != CHARS_AFTER_DECIMAL_POINT) {
      return FALSE;
   }

   return TRUE;
}

/*
 * Simply check for the following sequence of characters:
 *    1. Exactly 2 characters before the first forward slash (for the month)
 *    2. One forward slash
 *    3. Exactly 2 characters before the second forward slash (for the day)
 *    4. One forward slash
 *    5. Exactly 4 characters (for the year)
 *
 * Important note: this function ONLY checks for the correct placement of the
 * forward slashes. It does NOT validate if the remaining characters are
 * numbers. That will be handled later.
 */
Bool is_valid_date_format(const char *date_string) {

   int count = 0;

   /*
    * Check for a forward slash too soon (i.e. within the first 2 characters).
    * We need 2 charactes for the month (mm/dd/yyyy).
    */
   while(*date_string && count < MONTH_LENGTH - 1) {
      if(*date_string == '/') {
         return FALSE;
      }
      
      count++;
      ++date_string;
   }

   /*
    * Check for a forward slash at exactly the next (third) character.
    */
   if(*date_string != '/') {
      return FALSE;
   }

   ++date_string;
   count = 0;
   
   /*
    * Check for a forward slash too soon (i.e. within the next 2 characters).
    * We need 2 charactes for the day (mm/dd/yyyy).
    */
   while(*date_string && count < DAY_LENGTH - 1) {
      if(*date_string == '/') {
         return FALSE;
      }
      
      count++;
      ++date_string;
   }

   /*
    * Check for a forward slash at exactly the next (sixth) character.
    */
   if(*date_string != '/') {
      return FALSE;
   }

   /*
    * Check for another forward slash (this is an error). We want to ensure
    * there are no more forward slashes because other functions rely on the
    * correct placement of the forward slashes.
    */
   ++date_string;
   
   while(*date_string) {
      if(*date_string == '/') {
         return FALSE;
      }

      ++date_string;
   }

   return TRUE;
}

/*
 * Simply check for the following sequence of characters:
 *    1. Exactly 10 characters before the first pipe (for the date mm/dd/yyyy)
 *    2. One pipe character
 *    3. 3, 4, 5, 6, 7, 8, or 9 characters between the first and second pipes
 *       (for the amount in the form of -99999.99 to 99999.99)
 *    4. One last pipe character (we don't care about the description)
 */
Bool is_valid_line_format(const char *line) {

   int count = 0;

   /*
    * Check for a pipe too soon (i.e. within the first 10 characters). We
    * need 10 charactes for the date (mm/dd/yyyy).
    */
   while(*line && count < DATE_LENGTH - 1) {
      if(*line == '|') {
         return FALSE;
      }
      
      count++;
      ++line;
   }

   /*
    * Check for a pipe at exactly the next (eleventh) character.
    */
   if(*line != '|') {
      return FALSE;
   }

   ++line;
   count = 0;
   
   /*
    * Check for the second pipe within the range of between the next 3 and 9
    * characters. We need between 3 and 9 characters for the amount.
    */
   while(*line && count < AMOUNT_LENGTH_MAX - 1) {
      /*
       * If we find a pipe too soon (i.e. within the first three characters of
       * the amount.
       */
      if(*line == '|' && count < AMOUNT_LENGTH_MIN - 1) {
         return FALSE;
      }

      if(*line == '|') {
         return TRUE;
      }

      count++;
      ++line;
   }

   if(*line == '|') {
      return TRUE;
   }

   return FALSE;
}

/*
 * Checks to ensure new line character is found in budget transaction before an
 * excess of characters are read. Prevents fgets from being called muyltiple
 * times for one line of data.
 */
Bool is_valid_line_termination(const char *line, int line_length) {

   int count = 0;

   /*
    * Check to make sure the given line length is larger than the padding.
    * Otherwise, this could result in an infinite loop later in this function
    * because we would be checking if the count is greater than a negative
    * number (which will always be true).
    */
   if(line_length - PADDING < 1) {
      return FALSE;
   }

   while(*line) {
      ++count;

      /*
       * If we haven't found a new line character by a certain point.
       */
      if(*line != '\n' && count > line_length - PADDING) {
         return FALSE;
      }
      
      ++line;
   }

   return TRUE;
}