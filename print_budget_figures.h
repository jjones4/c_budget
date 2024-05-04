/*
 * Name:       print_budget_figures.h
 *
 * Purpose:    Function definitions for print_budget_figures.c
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

#ifndef PRINT_BUDGET_FIGURES_H

#define PRINT_BUDGET_FIGURES_H

void display_budget_figures(double *monthly_credits, double *monthly_debits,
   double *monthly_margins, double *large_amounts_credits, double
   *large_amounts_debits, double *large_amounts_margins, double
   *yearly_credits, double *yearly_debits, double *yearly_margins);

#endif