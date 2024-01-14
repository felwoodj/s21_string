#include "s21_sprintf.h"
// прототип : %[flags][width][.precision][length]specifier

int s21_sprintf(char *str, const char *format, ...) {
  Spec specs = {0};
  va_list arguments;
  va_start(arguments, format);
  char *str_start = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      s21_memset(&specs, 0, sizeof(Spec));  // обнуление флагов;
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
      *ret = str - str_start;
    }
  }
  *str = '\0';
  va_end(arguments);
  return (str - str_start);
}

const char *get_flags(const char *format, Spec *specs) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
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
      case '#':
        specs->hash = 1;
        break;
      case '0':
        specs->zero = 1;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, Spec *specs,
                      va_list arguments) {  // обработка ширины
  if (*format == '*') {
    format++;
    specs->width = va_arg(arguments, int);
  } else if (s21_isdigit(*format)) {
    char tmp[SIZE_BUFF] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    specs->width = s21_atoi(tmp);
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
    specs->precision = s21_atoi(tmp);
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
  int index = SIZE_BUFF - 2;  // последний элемент массива \0

  bool neg = val < 0 ? 1 : 0;  // проверка на знак
  val = neg ? -val : val;

  if (val == 0)
    tmp[index] =
        '0';  // если 0 то записываем 0
              // val = 9323 val % base(10) = 3, 3 символ в строке = '3'
              // tmp[12] = "0123456789abcdef"[9323 % 10] =
              // "0123456789abcdef"[3] tmp[12] = '3' - так как 3 символ
              // в строке "0123456789abcdef" это 3 tmp[11] =
              // "0123456789abcdef"[932 % 10] = "0123456789abcdef"[2]
              // tmp[11] = '2' - так как 2 символ в строке это 2
              // tmp[10] = "0123456789abcdef"[93 % 10] = "0123456789abcdef"[3]
  while (val > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[val % base];
    val /= base;
  }
  // tmp[index] != '\0', в начале записывается первый символ != '\0',
  for (int j = 0; tmp[index]; index++, j++) {
    if (neg && j == 0) {
      res[j++] = '-';  // если число отрицательное то в начале -
    }
    res[j] = tmp[index];  // запись в массив res
  }
}

void format_precision(char *buffer, Spec specs) {
  char tmp[SIZE_BUFF] = {'\0'};
  int sign = 0;
  int len = s21_strlen(buffer);  // длина буфера
  if (buffer[0] == '-') {  // если первый элемент массива -
    tmp[0] = '-';
    len--;
    sign = 1;
  }
  if (specs.precision > len) {  // если точность больше длины буфера
    int index = 0;
    for (index = sign; index < specs.precision - len + sign; index++)
      tmp[index] = '0';  // заполняем нулями
    for (int i = sign; buffer[i]; i++, index++)
      tmp[index] = buffer[i];  // переносим в массив tmp с заполненными нулями

    s21_strcpy(buffer, tmp);  // переносим обратно в итоговый массив buffer с
                              // заполненными нулями
  }
  if (specs.dot &&
      specs.precision == 0 &&  // если ничего не записалось в массив
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
  if (specs.flag_plus && specs.specifier != 'u' && specs.specifier != 'o') {
    tmp[0] = buffer[0] == '-'
                 ? buffer[0]
                 : '+';  // если первым - то записываем -, если + то +
    s21_strcpy(
        tmp + 1,
        buffer[0] == '-' ? buffer + 1 : buffer);  // записываем buffer в tmp
    s21_strcpy(buffer, tmp);
  } else if (specs.flag_space && buffer[0] != '-' && specs.specifier != 'u' &&
             specs.specifier != 'o') {  // если пробел
    tmp[0] = ' ';                       // первым идет пробел
    s21_strcpy(tmp + 1,
               buffer);  // buffer копируется в tmp + 1, +1 из за пробела
    s21_strcpy(buffer, tmp);  // потом tmp копируется в buffer
  }
  if (specs.width >
      (int)s21_strlen(buffer)) {  // если ширина больше длины buffer
    int index = specs.width - s21_strlen(buffer);  // находим разницу
    if (!specs.flag_minus) {  // если это не минус
      s21_memset(tmp, specs.zero ? '0' : ' ',
                 index);  // заполняем нулями или пробелами tmp
      s21_strcpy(tmp + index, buffer);  // копируем buffer в tmp + index
    } else {
      s21_strcpy(tmp, buffer);  // сначала копируем
      s21_memset(tmp + s21_strlen(tmp), ' ',
                 index);  // потом заполняем пробелами
    }
    s21_strcpy(buffer, tmp);  // переносим из tmp в buffer
  }
}

void parser(Spec specs, char *buffer, va_list arguments) {
  if (specs.specifier == 'd' || specs.specifier == 'i')
    parsing_int(specs, buffer, arguments);
  else if (specs.specifier == 'u')
    parsing_unsigned(specs, buffer, arguments);
  else if (specs.specifier == '%')
    buffer[0] = '%';
  else if (specs.specifier == 'o')
    parsing_o(specs, buffer, arguments);
  else if (specs.specifier == 'c')
    parsing_c(specs, buffer, arguments);
  else if (specs.specifier == 's')
    parsing_string(specs, buffer, arguments);
  else if (specs.specifier == 'f')
    parsing_float(specs, buffer, arguments);
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

void parsing_unsigned(Spec specs, char *buffer, va_list arguments) {
  uint64_t val = va_arg(arguments, uint64_t);
  switch (specs.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case '\0':
      val = (uint32_t)val;
      break;
  }
  unsigned_num_to_string(val, buffer, 10);
  format_precision(buffer, specs);
  format_flags(buffer, specs);
}

void unsigned_num_to_string(uint64_t val, char *ret, int base) {
  char buffer[SIZE_BUFF + 1] = {'\0'};  // потому что последний символ это '\0'
  int index = SIZE_BUFF - 1;  // потому что индексы в массиве начинаются с 0
  if (val == 0) {             // если 0 то записываем 0
    buffer[index] = '0';
    index--;
  }
  for (; val && index; --index, val /= base)  // пока val && index != 0
    buffer[index] = "0123456789abcdef"[val % base];
  for (int j = 0; buffer[index + 1]; index++, j++)
    ret[j] = buffer[index + 1];  // записываем в ret
}

void parsing_o(Spec specs, char *buffer, va_list arguments) {
  buffer[0] = '0';
  num_to_string(va_arg(arguments, s21_size_t), buffer + specs.hash, 8);
  format_precision(buffer, specs);
  format_flags(buffer, specs);
}

void parsing_c(Spec specs, char *buffer, va_list arguments) {
  if (specs.length == 'l') {
    wchar_t wide_char;
    wide_char = va_arg(arguments, wchar_t);
    format_wide_char(specs, buffer, wide_char);
  } else {
    char c;
    c = va_arg(arguments, s21_size_t);
    format_char(specs, buffer, c);
  }
}

void format_wide_char(Spec specs, char *buffer, char wide_char) {
  wchar_t wide_char_tmp = (wchar_t)wide_char;
  if (!specs.flag_minus && specs.width) {
    char tmp[SIZE_BUFF] = {'\0'};
    wcstombs(tmp, &wide_char_tmp,
             SIZE_BUFF);  // записывае тв tmp широкие символы
    for (s21_size_t i = 0; i < specs.width - s21_strlen(tmp); i++)
      buffer[i] = ' ';  // заполняет пробелами до указанной ширины
    s21_strcat(buffer, tmp);  // переписывает tmp в конец buffer
  } else if (specs.width) {  // если задана только ширина
    wcstombs(buffer, &wide_char_tmp,
             SIZE_BUFF);  // записывает в tmp широкие символы
    for (int i = s21_strlen(buffer); i < specs.width; i++)
      buffer[i] = ' ';  // заполняет пробелами до указанной ширины
  } else {
    wcstombs(buffer, &wide_char_tmp, SIZE_BUFF);
  }
}

void format_char(Spec specs, char *buffer, char c) {
  if (!specs.flag_minus && specs.width) {  // если это не минус и есть ширина
    for (int i = 0; i < specs.width; i++) {  // записываем пробелы
      buffer[i] = ' ';
      if (i == specs.width -
                   1)  // если i это последний элемент буфера то записываем c
        buffer[i] = c;
    }
  } else if (specs.width) {  // если задана только ширина
    buffer[0] = c;  // записываем с в первый элемент
    for (int i = 1; i < specs.width; i++)
      buffer[i] = ' ';  // записываем пробелами
  } else {
    buffer[0] = c;  // если ничего не записалось то записываем символ с
  }
}

void parsing_string(Spec specs, char *buffer, va_list arguments) {
  if (specs.length == 'l') {
    wchar_t *wchar = va_arg(arguments, wchar_t *);
    format_wide_string(specs, buffer, wchar);
  } else {
    char *string = va_arg(arguments, char *);
    format_string(specs, buffer, string);
  }
}

void format_string(Spec specs, char *buffer, char *string) {
  if (string == NULL) {
    s21_strcat(buffer, "(null)");
  } else {
    char tmp[SIZE_BUFF] = {'\0'};
    s21_strcpy(tmp, string);
    if (specs.dot) tmp[specs.precision] = '\0';
    int len = s21_strlen(tmp);
    int shift = specs.width - len;  // кол-во пробелов

    if (specs.flag_minus && shift > 0) {
      s21_strcpy(buffer, tmp);
      s21_memset(buffer + len, ' ', shift);
    } else if (shift > 0) {
      s21_memset(buffer, ' ', shift);
      s21_strcpy(buffer + shift, tmp);
    } else {
      s21_strcpy(buffer, tmp);
    }
  }
}

void format_wide_string(Spec specs, char *buffer, wchar_t *wchar) {
  if (wchar == NULL) {
    s21_strcat(buffer, "(null)");
  } else {
    char tmp[SIZE_BUFF] = {'\0'};
    char str[SIZE_BUFF] = {'\0'};

    wcstombs(str, wchar, SIZE_BUFF);
    s21_strcpy(tmp, str);

    if (specs.dot) tmp[specs.precision] = '\0';

    int len = s21_strlen(tmp);
    int shift = specs.width - len;
    if (specs.flag_minus && specs.width) {
      s21_strcpy(buffer, tmp);
      s21_memset(buffer + len, ' ', shift);
    } else if (specs.width) {
      s21_memset(buffer + len, ' ', len);
      s21_strcpy(buffer, tmp);
    } else {
      s21_strcpy(buffer, tmp);
    }
  }
}

void parsing_float(Spec specs, char *buffer, va_list arguments) {
  long double val = 0;
  if (specs.length == 'L') {
    val = va_arg(arguments, long double);
  } else {
    val = va_arg(arguments, double);
  }
  if (!specs.dot) specs.precision = 6;
  double_to_string(val, buffer, specs);
  format_flags(buffer, specs);
}

void double_to_string(long double val, char *ret, Spec specs) {
  // val = 1.1235
  char buffer[SIZE_BUFF] = {'\0'};  // заполняем нулями
  int index = SIZE_BUFF - 2;  // потому что последний символ это \0
  bool neg = val < 0 ? 1 : 0;  // проверка на знак
  val = neg ? val * -1 : val;
  long double l = 0;  // 1
  long double r =
      modfl(val, &l);  // 0.123499 - берет дробную часть,целую пихает в l
  if (specs.precision == 0) {  // если точность не указана
    l = roundl(val);           // округляет до целого
    r = 0;
  }
  char tmp[SIZE_BUFF] = {'\0'};  // заполняем нулями
  for (int i = 0; i < specs.precision;
       i++) {  // циклом берем первые 6 символов дробной части
    r *= 10;
    tmp[i] = (int)r + '0';  // переводим r в строку и получаем 123499
  }
  long long right = roundl(r),
            left = l;  // округляем дробную часть и получаем целое число left
                       // =123500, right =1;
  if (right == 0) {
    for (int i = 0; i < specs.precision; index--, i++) buffer[index] = '0';
  } else {
    for (int i = s21_strlen(tmp); right || i > 0; right /= 10, index--, i--)
      buffer[index] =
          (int)(right % 10 + 0.05) + '0';  // записываем в buffer наш right
  }
  if ((specs.dot && specs.precision != 0) || (int)r ||
      (!specs.dot && val == 0) || s21_strlen(tmp))
    buffer[index--] = '.';
  if (left == 0) {
    buffer[index] = '0';
    index--;
  } else {
    for (; left; left /= 10, index--) buffer[index] = (int)(left % 10) + '0';
  }
  for (int i = 0; buffer[index + 1]; index++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buffer[index + 1];
  }
}

bool s21_isdigit(char c) {
  return (c >= '0' && c <= '9');
}  // проверка на число

// d u f c s o
// s не проходит с точкой и числами большими
// int main() {
//   // "%s Test %3.s Test %5.7s TEST %10s %s %-s %+s %.s % .s";
//   // %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc
//   char str1[400];
//   char str2[400];
//   char *str3 = "test: %15.13f! test: %26.15f!";
//   double num = -365289.34628654873789362746834;
//   s21_sprintf(str1, str3, num, num);
//   sprintf(str2, str3, num, num);

//   printf("%s\n", str1);
//   printf("%s\n", str2);
//   return 0;
// }
