/*
 * Name:       print_budget_figures.h
 *
 * Purpose:    Function for displaying the budget figures in tables to stdout.
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
#include "size_limits.h"
#include "print_budget_figures.h"

void display_yearly_figures(double *yearly_credits, double *yearly_debits,
   double *yearly_margins);
void display_large_transactions(double *large_amounts_credits, double
   *large_amounts_debits, double *large_amounts_margins);
void display_monthly_figures(double *monthly_credits, double *monthly_debits,
   double *monthly_margins);

void display_budget_figures(double *monthly_credits, double *monthly_debits,
   double *monthly_margins, double *large_amounts_credits, double
   *large_amounts_debits, double *large_amounts_margins, double
   *yearly_credits, double *yearly_debits, double *yearly_margins) {

   display_yearly_figures(yearly_credits, yearly_debits, yearly_margins);
   display_large_transactions(large_amounts_credits, large_amounts_debits,
      large_amounts_margins);
   display_monthly_figures(monthly_credits, monthly_debits, monthly_margins);
}

void display_yearly_figures(double *yearly_credits, double *yearly_debits,
   double *yearly_margins) {

   int i;

   printf("\n   YEARLY TOTALS\n\n");

   for(i = 0; i < NUMBER_OF_YEARS; i++) {
      if(yearly_credits[i] != 0.00 || yearly_debits[i] != 0.00) {
         printf("%6s%-10s%10d%18.2f%18.2f%18.2f\n", "", "",
            START_YEAR + i, yearly_credits[i], yearly_debits[i],
            yearly_margins[i]);
      }
   }

   printf("\n   AVERAGE MONTHLY FIGURES FOR EACH YEAR\n\n");

   for(i = 0; i < NUMBER_OF_YEARS; i++) {
      if(yearly_credits[i] != 0.00 || yearly_debits[i] != 0.00) {
         printf("%6s%-10s%10d%18.2f%18.2f%18.2f\n", "", "",
            START_YEAR + i, yearly_credits[i] / 12, yearly_debits[i] / 12,
            yearly_margins[i] / 12);
      }
   }
}

void display_large_transactions(double *large_amounts_credits, double
   *large_amounts_debits, double *large_amounts_margins) {

   int i;

   const char* month_names[] = { "January", "February", "March", "April",
      "May", "June", "July", "August", "September", "October", "November",
      "December"};

   printf("\n   LARGE TRANSACTIONS\n\n");

   for(i = 0; i < NUMBER_OF_MONTHS; i++) {
      if(large_amounts_credits[i] != 0.00 || large_amounts_debits[i] != 0.00) {
         printf("%6s%-10s%10d%18.2f%18.2f%18.2f\n",
           "", month_names[i % 12], ((i - (i % 12)) / 12) + START_YEAR,
           large_amounts_credits[i], large_amounts_debits[i],
           large_amounts_margins[i]);
      }
   }
}

void display_monthly_figures(double *monthly_credits, double *monthly_debits,
   double *monthly_margins) {

   int i;

   const char* month_names[] = { "January", "February", "March", "April",
      "May", "June", "July", "August", "September", "October", "November",
      "December"};

   printf("\n   MONTHLY TRANSACTIONS\n\n");

   for(i = 0; i < NUMBER_OF_MONTHS; i++) {
      if(monthly_credits[i] != 0.00 || monthly_debits[i] != 0.00) {
         printf("%6s%-10s%10d%18.2f%18.2f%18.2f\n",
           "", month_names[i % 12], ((i - (i % 12)) / 12) + START_YEAR,
           monthly_credits[i], monthly_debits[i],
           monthly_margins[i]);
      }
   }
}