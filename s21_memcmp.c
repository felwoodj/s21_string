#include "s21_string.h"

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *s1_p = s1, *s2_p = s2;
  while (n--) {
    if (*s1_p != *s2_p) {
      return *s1_p - *s2_p;
    }
    s1_p++;
    s2_p++;
  }
  return 0;
}