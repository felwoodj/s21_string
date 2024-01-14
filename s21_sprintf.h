#ifndef _S21_SPRINTF_H
#define _S21_SPRINTF_H

#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#define s21_NULL (void *)0;

typedef struct {
  int flag_plus;   // знак
  int flag_minus;  // к левому краю
  int flag_space;  // + символ под знак
  int width;       // ширина
  int precision;   // точность
  int zero;        // 0
  int dot;  // наличие точки (говорит о наличии точности в числе)
  char length;     // тип переменной (%lf Lf Ld и тд) l h L
  char specifier;  // спецификатор
  char hash;       // #
} Spec;

const char *get_flags(const char *format, Spec *specs);
const char *get_width(const char *format, Spec *specs, va_list arguments);
const char *get_precision(const char *format, Spec *specs, va_list arguments);
const char *get_length(const char *format, Spec *specs);
void parser(Spec specs, char *buffer, va_list arguments);
void num_to_string(long int val, char *res, int base);
void parsing_int(Spec specs, char *buffer, va_list arguments);
void parsing_unsigned(Spec specs, char *buffer, va_list arguments);
void unsigned_num_to_string(uint64_t val, char *ret, int base);
void parsing_o(Spec specs, char *buffer, va_list arguments);
void format_char(Spec specs, char *buffer, char c);
void format_wide_char(Spec specs, char *buffer, char wide_char);
void parsing_c(Spec specs, char *buffer, va_list arguments);
void format_wide_string(Spec specs, char *buffer, wchar_t *wchar);
void format_string(Spec specs, char *buffer, char *string);
void parsing_string(Spec specs, char *buffer, va_list arguments);
void parsing_float(Spec specs, char *buffer, va_list arguments);
void parsing_float(Spec specs, char *buffer, va_list arguments);
void double_to_string(long double val, char *ret, Spec specs);
bool check_int_specifier(char c);
bool s21_isdigit(char c);
void parser(Spec specs, char *buffer, va_list arguments);
int s21_atoi(const char *str_carriage);
#endif