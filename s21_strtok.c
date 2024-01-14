#include "s21_string.h"

char *olds;
char *s21_strtok(char *str, const char *delim) {
  char *token = S21_NULL;
  if (str == S21_NULL) str = olds;

  str += s21_strspn(str, delim);
  if (*str == '\0') {
    olds = str;
    return S21_NULL;
  }
  token = str;
  str = s21_strpbrk(token, delim);
  if (str == S21_NULL) {
    olds = s21_memchr(token, '\0', 1024);
  } else {
    *str = '\0';
    olds = str + 1;
  }
  return token;
}