/*
 * Name:       c_budget.c
 *
 * Purpose:    Main program source file
 *
 *             c_budget is a simple command-line budget app which validates and
 *             displays budget figures. The budget data is stored in a text
 *             file called budget_data.txt. Additionally, a custom file name
 *             can be used. c_budget can display figures such as monthly and
 *             yearly income and expenses and show how much over or under
 *             budget you were for those time periods.
 *
 *             c_budget is run from the command line with no arguments after
 *             the program name or with one argument after the program name, as
 *             shown below:
 *                1. c_budget
 *                2. c_budget my_budget_data.txt
 *
 *             If no arguments are provided, c_budget uses the file defined in
 *             the macro DEFAULT_DATA_FILE. If the user enters a user-defined
 *             name for the data file, c_budget will attempt to use it.
 *
 *             c_budget is designed  to be C89 compliant. Therefore, it does
 *             not utilize <stdbool.h>, variable length arrays, double forward
 *             slashes for comments, etc.
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
#include "size_limits.h"
#include "return_codes.h"
#include "program_init.h"
#include "validate_budget_line.h"
#include "budget_calculations.h"
#include "print_budget_figures.h"

#define MAX_NUMBER_OF_TRANSACTIONS 1000000

int main(int argc, char **argv)
{
   FILE *fp;
   char *data_file_name = NULL;
   data_file_name = malloc(FILE_NAME_LENGTH + 1);
   char *line = NULL;
   int line_number = 0;
   int program_init_result = 0;
   int validate_budget_line_result = 0;
   int calculate_budget_figures_result = 0;
   double monthly_debits[NUMBER_OF_MONTHS] = {0.00};
   double monthly_credits[NUMBER_OF_MONTHS] = {0.00};
   double monthly_margins[NUMBER_OF_MONTHS] = {0.00};
   double large_amounts_credits[NUMBER_OF_MONTHS] = {0.00};
   double large_amounts_debits[NUMBER_OF_MONTHS] = {0.00};
   double large_amounts_margins[NUMBER_OF_MONTHS] = {0.00};
   double yearly_debits[NUMBER_OF_YEARS] = {0.00};
   double yearly_credits[NUMBER_OF_YEARS] = {0.00};
   double yearly_margins[NUMBER_OF_YEARS] = {0.00};

   /*
    * Ensure program initialization is successful. If successful,
    * data_file_name will point to the budget data file. If not, return
    * appropriate error code.
    */
   program_init_result = program_init(argc, argv, &data_file_name);

   if(program_init_result != 0) {
      return program_init_result;
   }

   (void) fopen_s(&fp, data_file_name, "r");

   if(fp == NULL) {
      printf("\nFile could not be opened. Please ensure %s ", data_file_name);
      printf("exists, and try again.\n");

      return FILE_ERROR;
   }

   /*
    * Get each line from budget data file. Perform validation checks and
    * calculations.
    */
   for(;;) {
      if(line_number > MAX_NUMBER_OF_TRANSACTIONS) {
         printf("\nToo much data was found in the budget data file.\n");

         return DATA_SIZE_ERROR;
      }

      line = malloc(LINE_BUFFER_SIZE * sizeof(char));

      if(line == NULL) {
         printf("\nThere was an error getting the required memory.\n");

         return MEMORY_ERROR;
      }

      if(fgets(line, LINE_BUFFER_SIZE - 1, fp) == NULL) {
         free(line);
         
         break;
      }

      validate_budget_line_result = validate_budget_line(&line, line_number);

      if(validate_budget_line_result != 0) {
         free(line);
         free(data_file_name);

         return validate_budget_line_result;
      }

      calculate_budget_figures_result = calculate_budget_figures(&line,
         monthly_credits, monthly_debits, monthly_margins,
         large_amounts_credits, large_amounts_debits, large_amounts_margins,
         yearly_credits, yearly_debits, yearly_margins);

      if(calculate_budget_figures_result != 0) {
         free(line);
         free(data_file_name);

         return calculate_budget_figures_result;
      }

      line_number++;

      free(line);
   }

   display_budget_figures(monthly_credits, monthly_debits, monthly_margins,
         large_amounts_credits, large_amounts_debits, large_amounts_margins,
         yearly_credits, yearly_debits, yearly_margins);

   fclose(fp);

   free(data_file_name);

   return 0;
}
