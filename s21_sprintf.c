#include "s21_sprintf.h"
// прототип : %[flags][width][.precision][length]specifier
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sprintf.h"
// спецификаторы: с, d, f, s, u, %
// флаги: -, +, (пробел)
// ширина: (число)
// точность: .(число)
// длина: l, h

// s21_sprintf(char *str, const char *format, ...)
// s21_sprintf(str, "hello %d %s %d, 123,'s,12346")

int s21_sprintf(char *str, const char *format, ...) {
  Spec specs = {0};
  va_list arguments;
  va_start(arguments, format);
  char *src = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      memset(&specs, 0, sizeof(Spec));  // обнуление флагов;
      format++;
    }

    format = get_flags(format, &specs);
    format = get_width(format, &specs, arguments);
    format = get_precision(format, &specs, arguments);
    format = get_length(format, &specs);

    specs.specifier = *format;
    format++;

    char buffer[SIZE_BUFF] = {'\0'};
    parser(specs, buffer, arguments);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];

    if (specs.specifier == 'n') {
      int *ret = va_arg(arguments, int *);
      *ret = str - src;
    }
  }
  *str = '\0';
  va_end(arguments);
  return (str - src);
}

const char *get_flags(const char *format, Spec *specs) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        specs->flag_minus = 1;
        break;
      case ' ':
        specs->flag_space = 1;
        break;
      case '+':
        specs->flag_plus = 1;
        break;
    }
    format++;
  }
  return format;
}

// s21_sprintf(str,"Hello %14.6d",148)
// width = 0 * 10 => 0 + ('1'-'0') == 0 + (49-48) => 1; по таблице ASCII
// width = 1 * 10 => 10 + ('4'-'0') == 10 + 4 => 14;
const char *get_width(const char *format, Spec *specs,
                      va_list arguments) {  // обработка ширины
  if (*format == '*') {
    format++;
    specs->width = va_arg(arguments, int);
  } else if (s21_isdigit(*format)) {
    char tmp[SIZE_BUFF] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    specs->width = atoi(tmp);
  }
  return format;
}

const char *get_precision(const char *format, Spec *specs, va_list arguments) {
  if (*format == '.') {
    specs->dot = 1;
    format++;
  }
  if (*format == '*') {
    format++;
    specs->precision = va_arg(arguments, int);
  }
  if (s21_isdigit(*format)) {
    char tmp[SIZE_BUFF] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    specs->precision = atoi(tmp);
  }
  return format;
}

const char *get_length(const char *format, Spec *specs) {
  switch (*format) {
    case 'h':
      specs->length = 'h';
      format++;
      break;
    case 'l':
      specs->length = 'l';
      format++;
      break;
    case 'L':
      specs->length = 'L';
      format++;
      break;
  }
  return format;
}

void num_to_string(long int val, char *res, int base) {
  char tmp[SIZE_BUFF] = {'\0'};
  int index = SIZE_BUFF - 2;  // 9 - индекс это \0

  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[index] = '0';  // если 0 то записываем 0

  while (val > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[index]; index++, j++) {
    if (neg && j == 0) {
      res[j++] = '-';
    }
    res[j] = tmp[index];
  }
}

void format_precision(char *buffer, Spec specs) {
  char tmp[SIZE_BUFF] = {'\0'};
  int sign = 0;
  int len = strlen(buffer);
  if (buffer[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }
  if (specs.precision > len) {
    int index = 0;
    for (index = sign; index < specs.precision - len + sign; index++)
      tmp[index] == '0';
    for (int i = sign; buffer[i]; i++, index++) tmp[index] = buffer[i];

    strcpy(buffer, tmp);
  }
  if (specs.dot && specs.precision == 0 &&
      check_int_specifier(specs.specifier) && buffer[0] == '0')
    buffer[0] = '\0';
}

bool check_int_specifier(char c) {
  char spec[] = {'d', 'i', 'o', 'u'};
  int res = 0;
  for (s21_size_t i = 0; i < sizeof(spec); i++) {
    if (spec[i] == c) {
      res = 1;
      break;
    }
  }
  return res;
}

void format_flags(char *buffer, Spec specs) {
  char tmp[SIZE_BUFF + 1] = {'\0'};  // + 1 из за '\0'
  if (specs.flag_plus && specs.specifier != 'u') {
    tmp[0] = buffer[0] == '-' ? buffer[0] : '+';
    strcpy(tmp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    strcpy(buffer, tmp);
  } else if (specs.flag_space && buffer[0] != '-' && specs.specifier != 'u') {
    tmp[0] = ' ';
    strcpy(tmp + 1, buffer);
    strcpy(buffer, tmp);
  }
  if (specs.width > (int)strlen(buffer)) {
    int index = specs.width - strlen(buffer);
    if (!specs.flag_minus) {
      memset(tmp, specs.zero ? '0' : ' ', index);
      strcpy(tmp + index, buffer);
    } else {
      strcpy(tmp, buffer);
      memset(tmp + strlen(tmp), ' ', index);
    }
    strcpy(buffer, tmp);
  }
}

void parser(Spec specs, char *buffer, va_list arguments) {
  if (specs.specifier == 'd' || specs.specifier == 'i')
    parsing_int(specs, buffer, arguments);
}

void parsing_int(Spec specs, char *buffer, va_list arguments) {
  int64_t val = va_arg(arguments, int64_t);  // длина l
  switch (specs.length) {
    case '\0':  // если ничего не выставлено(\0), так как структуру каждый раз
                // зануляем
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  num_to_string(val, buffer, 10);
  format_precision(buffer, specs);
  format_flags(buffer, specs);
}

bool s21_isdigit(char c) { return (c >= '0' && c <= '9'); }
// d
// %d %d
// ld hd
// 3d 5d
// 6.5d .23 3.d не прошел
// -10.5d %-.8d
int main() {
  char str1[100] = "";
  char str2[100] = "";
  int val = -98373;
  int val2 = 101223;

  s21_sprintf(str1, "Test %6.5d %.9d Test", val, val2);
  sprintf(str2, "Test %6.5d %.9d Test", val, val2);
  printf("%s\n", str1);
  printf("%s\n", str2);
  return 0;
}
