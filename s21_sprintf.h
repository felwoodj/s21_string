#ifndef _S21_SPRINTF_H
#define _S21_SPRINTF_H

#include <locale.h>

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
} Spec;

int s21_sprintf(char *str, const char *format, ...);

const char *get_flags(const char *format, Spec *specs);
const char *get_width(const char *format, Spec *specs, va_list arguments);
const char *get_precision(const char *format, Spec *specs, va_list arguments);
const char *get_length(const char *format, Spec *specs);
void parser(Spec specs, char *buffer, va_list arguments);
void num_to_string(long int val, char *res, int base);
void parsing_int(Spec specs, char *buffer, va_list arguments);
bool check_int_specifier(char c);
bool s21_isdigit(char c);
void parser(Spec specs, char *buffer, va_list arguments);

#endif