#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *first = str;
  while (n--) {
    if (*first == (unsigned char)c) {
      return (void *)first;
    }
    first++;
  }
  return NULL;
}
