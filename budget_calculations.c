/*
 * Name:       budget_calculations.c
 *
 * Purpose:    Functions for calculating all desired budget figures.
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

/*
 * Any income/gift over $3,000.00 goes into a different table so it doesn't
 * skew my monthly figures or my averages.
 */
#define LARGE_INCOME_THRESHHOLD 3000.00

/*
 * Any expense over $2,400.00 goes into a different table so it doesn't skew my
 * monthly figures or my averages.
 */
#define LARGE_EXPENSE_THRESHHOLD (-2400.00)

#include <stdio.h>
#include <stdlib.h>
#include "size_limits.h"
#include "return_codes.h"
#include "get_data.h"

int calculate_budget_figures(char **line, double *monthly_credits,
   double *monthly_debits, double *monthly_margins, double
   *large_amounts_credits, double *large_amounts_debits, double
   *large_amounts_margins, double *yearly_credits, double *yearly_debits,
   double *yearly_margins) {
   
   int array_index_for_monthly_figures = 0;
   int array_index_for_yearly_figures = 0;
   int month = 0; int year = 0;
   int error_code = 0;
   double amount = 0.00;
   char *date_string = NULL;
   char *amount_string = NULL;

   date_string = malloc(DATE_LENGTH * sizeof(char));
   amount_string = malloc(AMOUNT_LENGTH_MAX * sizeof(char));
   
   if(date_string == NULL || amount_string == NULL) {
      printf("\nThere was an error getting the required memory.\n");

      return MEMORY_ERROR;
   }

   get_date_string(*line, date_string);
   get_amount_string(*line, amount_string);

   month = get_month(date_string, &error_code);

   if(error_code == MEMORY_ERROR) {
      printf("\nThere was an error getting the required memory.\n");

      free(date_string);
      free(amount_string);

      return MEMORY_ERROR;
   }

   year = get_year(date_string, &error_code);

   if(error_code == MEMORY_ERROR) {
      printf("\nThere was an error getting the required memory.\n");

      free(date_string);
      free(amount_string);

      return MEMORY_ERROR;
   }
   
   amount = get_amount(amount_string);

   array_index_for_monthly_figures = 12 * (year - START_YEAR) + month - 1;
   array_index_for_yearly_figures = year - START_YEAR;

   if(amount < -2400.00) {
      large_amounts_debits[array_index_for_monthly_figures] += amount;
      large_amounts_margins[array_index_for_monthly_figures] += amount;
   }
   else if(amount < 0) {
      monthly_debits[array_index_for_monthly_figures] += amount;
      yearly_debits[array_index_for_yearly_figures] += amount;

      monthly_margins[array_index_for_monthly_figures] += amount;
      yearly_margins[array_index_for_yearly_figures] += amount;
   }
   else if(amount < 3000.00) {
      monthly_credits[array_index_for_monthly_figures] += amount;
      yearly_credits[array_index_for_yearly_figures] += amount;

      monthly_margins[array_index_for_monthly_figures] += amount;
      yearly_margins[array_index_for_yearly_figures] += amount;
   }
   else {
      large_amounts_credits[array_index_for_monthly_figures] += amount;
      large_amounts_margins[array_index_for_monthly_figures] += amount;
   }

   free(date_string);
   free(amount_string);

   return 0;
}