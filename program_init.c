/*
 * Name:       program_init.c
 *
 * Purpose:    Perform initial checks and initialization to get required data
 *             from data file and set up the program's data structure for the
 *             budget. The data structure is a linked list that will be sorted
 *             using qsort.
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

#include <stdlib.h>
#include <string.h>
#include "program_init.h"
#include "return_codes.h"

Bool arg_count_within_range(int argument_count);
Bool string_length_within_range(const char *s, int maximum_string_length);
Bool is_default_data_file_used(int argument_count);
Bool is_valid_data_file_name_length(Bool default_data_file_used,
   char **arg_vector);
void get_data_file_name(Bool default_data_file_used, char *default_data_file,
   char **arg_vector);

/*
 * Return 0 to main function if all initializations and checks succeed. Return
 * applicable error code, otherwise (see return_codes.h).
 */
int program_init(int argument_count, char **argument_vector,
   char **data_file_name) {

   char *data_file = NULL;

   /*
    * Ensure number of command-line arguments given does not exceed maximum
    * number of allowable arguments.
    */
   if(arg_count_within_range(argument_count) == FALSE) {
      printf("\nUp to one argument allowed after program name.\n");

      return ARGUMENT_ERROR;
   }

   data_file = malloc(FILE_NAME_LENGTH + 1);

   if(data_file == NULL) {
      printf("\nMemory could not be allocated.\n");

      return MEMORY_ERROR;
   }

   /*
    * Make sure the data file name length is within the valid range. Based on
    * the number of command-line arguments provided, it is determined whether
    * the user is entering a name for the data file or is using the default
    * data file.
    */
   if(is_valid_data_file_name_length(is_default_data_file_used(argument_count),
      argument_vector) == FALSE) {

      printf("\nData file name exceeds maximum number of %d",
            FILE_NAME_LENGTH);
      printf(" allowable characters.\n");

      return FILE_ERROR;
   }

   /*
    * If get_data_file_name is successful, data_file will point to the data
    * file name, which can be used to open the file later. Based on the number
    * of command-line arguments provided, it is determined whether the user is
    * entering a name for the data file or is using the default data file.
    */
   (void) get_data_file_name(is_default_data_file_used(argument_count), data_file,
      argument_vector);

   (void) strcpy_s(*data_file_name, FILE_NAME_LENGTH, data_file);

   free(data_file);

   return 0;
}

Bool is_default_data_file_used(int argument_count) {
   if(argument_count > 1) {
      return FALSE;
   }
   else {
      return TRUE;
   }
}

Bool arg_count_within_range(int argument_count) {
   if(argument_count > MAX_ARG_COUNT || argument_count < MIN_ARG_COUNT) {
      return FALSE;
   }
   else {
      return TRUE;
   }
}

Bool string_length_within_range(const char *s, int maximum_string_length)
{
   int i = 0;

   while(*s) {
      s++;
      i++;

      if(i > maximum_string_length) {
         return FALSE;
      }
   }

   return TRUE;
}

Bool is_valid_data_file_name_length(Bool default_data_file_used,
   char **arg_vector) {

   if(default_data_file_used == TRUE) {
      if(!string_length_within_range(DEFAULT_DATA_FILE, FILE_NAME_LENGTH)) {

         return FALSE;
      }
   }
   else {
      if(!string_length_within_range(*++arg_vector, FILE_NAME_LENGTH)) {

         return FALSE;
      }
   }

   return TRUE;
}

void get_data_file_name(Bool default_data_file_used, char *data_file_name,
   char **arg_vector) {
   
   if(default_data_file_used == TRUE) {

      (void) strcpy_s(data_file_name, FILE_NAME_LENGTH, DEFAULT_DATA_FILE);
   }
   else {
      
      (void) strcpy_s(data_file_name, FILE_NAME_LENGTH, *++arg_vector);
   }
}
