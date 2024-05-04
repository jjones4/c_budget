/*
 * Name:       budget_calculations.h
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

#ifndef BUDGET_CALCULATIONS_H

#define BUDGET_CALCULATIONS_H

int calculate_budget_figures(char **line, double *monthly_credits,
   double *monthly_debits, double *monthly_margins, double
   *large_amounts_credits, double *large_amounts_debits, double
   *large_amounts_margins, double *yearly_credits, double *yearly_debits,
   double *yearly_margins);

#endif