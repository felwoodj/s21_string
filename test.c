#include <check.h>

#include "s21_string.h"

START_TEST(s21_strlen_test) {
  int n = 6;
  char *str[] = {"qazxsw",      ";;;;;;;;;;;;;;;", "schooll 21",
                 "QQQQQQQQQQQ", "1234567890",      "lana annnnnna"};
  for (int i = 0; i < n; i++) {
    ck_assert_int_eq(strlen(str[i]), s21_strlen(str[i]));
  }
  char str2[] = "\0";
  char str3[] = "     ";
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -100; i < 250; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
  char ch = '?';
  ck_assert_str_eq(strerror(ch), s21_strerror(ch));
  ck_assert_str_eq(strerror(-1000), s21_strerror(-1000));
  ck_assert_str_eq(strerror(0), s21_strerror(0));
}
END_TEST

START_TEST(s21_memchr_test) {
  char src[] = "01234567890";
  for (int i = 48; i <= 57; i++) {
    ck_assert_ptr_eq(memchr(src, (char)i, 10), s21_memchr(src, (char)i, 10));
  }

  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 97; i <= 122; i++) {
    ck_assert_ptr_eq(memchr(alphabet, (char)i, 25),
                     s21_memchr(alphabet, (char)i, 25));
  }

  char alphabet_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 65; i <= 90; i++) {
    ck_assert_ptr_eq(memchr(alphabet_upper, (char)i, 25),
                     s21_memchr(alphabet_upper, (char)i, 25));
  }

  char nan[] = "AAAAAAAA";
  ck_assert_ptr_eq(memchr(nan, 'a', 10), s21_memchr(nan, 'a', 10));
  ck_assert_ptr_eq(memchr(nan, 'A', 10), s21_memchr(nan, 'A', 10));
  ck_assert_ptr_eq(memchr(nan, 'B', 10), s21_memchr(nan, 'B', 10));
}
END_TEST

START_TEST(s21_memcpy_test) {
  char dest[100];
  char string[] = "01234567890123456789";
  for (s21_size_t i = 2; i < 20; i++) {
    ck_assert_ptr_eq(memcpy(dest, string, i), s21_memcpy(dest, string, i));
  }
}
END_TEST

START_TEST(s21_strrchr_test) {
  char str[100] = "1234567890";
  for (int i = 48; i <= 57; i++) {
    char *ptr1 = s21_strrchr(str, i);
    char *orig1 = strrchr(str, i);
    ck_assert_str_eq(ptr1, orig1);
  }

  char str1[100] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 97; i <= 122; i++) {
    char *ptr1 = s21_strrchr(str1, i);
    char *orig1 = strrchr(str1, i);
    ck_assert_str_eq(ptr1, orig1);
  }

  char str2[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 65; i <= 90; i++) {
    char *ptr1 = s21_strrchr(str2, i);
    char *orig1 = strrchr(str2, i);
    ck_assert_str_eq(ptr1, orig1);
  }
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdyfghijklmnopqrstuvwxyz";

  int my1 = s21_strncmp(str1, str2, 3) > 0 ? 1 : -1;
  int orig1 = strncmp(str1, str2, 3) > 0 ? 1 : -1;
  ck_assert_int_eq(orig1, my1);

  int my2 = s21_strncmp(str1, str2, 5) > 0 ? 1 : -1;
  int orig2 = strncmp(str1, str2, 5) > 0 ? 1 : -1;
  ck_assert_int_eq(orig2, my2);

  int my3 = s21_strncmp(str1, str2, 20) > 0 ? 1 : -1;
  int orig3 = strncmp(str1, str2, 20) > 0 ? 1 : -1;
  ck_assert_int_eq(orig3, my3);

  int my4 = s21_strncmp(str1, str2, 10) > 0 ? 1 : -1;
  int orig4 = strncmp(str1, str2, 10) > 0 ? 1 : -1;
  ck_assert_int_eq(orig4, my4);
}
END_TEST

START_TEST(s21_strncat_test) {
  char syms[100] = "0123456789";
  char syms_reverse[100] = "9876543210";
  char string[100] = "01234567890123456789";
  char alphabet_upper[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char no_syms[100] = "";

  ck_assert_str_eq(strncat(syms, syms_reverse, 10),
                   s21_strncat(syms, syms_reverse, 10));
  ck_assert_str_eq(strncat(string, alphabet_upper, 1),
                   s21_strncat(string, alphabet_upper, 1));
  ck_assert_str_eq(strncat(syms, alphabet_upper, 5),
                   s21_strncat(syms, alphabet_upper, 5));
  ck_assert_str_eq(strncat(no_syms, alphabet_upper, 3),
                   s21_strncat(no_syms, alphabet_upper, 3));
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str1[100] = "abcdefghijklmnopqrstuvwxyz";
  char str1_cp[25] = {0};
  char str2[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str2_cp[25] = {0};
  char str3[100] = "1234567890";
  char str3_cp[10] = "9876543210";

  ck_assert_str_eq(strncpy(str1_cp, str1, 3), s21_strncpy(str1_cp, str1, 3));
  ck_assert_str_eq(strncpy(str1_cp, str1, 10), s21_strncpy(str1_cp, str1, 10));
  ck_assert_str_eq(strncpy(str2_cp, str2, 5), s21_strncpy(str2_cp, str2, 5));
  ck_assert_str_eq(strncpy(str2_cp, str2, 15), s21_strncpy(str2_cp, str2, 15));
  ck_assert_str_eq(strncpy(str3_cp, str3, 1), s21_strncpy(str3_cp, str3, 1));
  ck_assert_str_eq(strncpy(str3_cp, str3, 10), s21_strncpy(str3_cp, str3, 10));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char str1[] = "0123456789";
  char str1_in[] = "987";

  char str2[] = "abced";
  char str2_in[] = "ecd";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";
  char str3_not[] = "abc";

  ck_assert_int_eq(strcspn(str1, str1_in), s21_strcspn(str1, str1_in));
  ck_assert_int_eq(strcspn(str2, str2_in), s21_strcspn(str2, str2_in));
  ck_assert_int_eq(strcspn(str3, str3_in), s21_strcspn(str3, str3_in));
  ck_assert_int_eq(strcspn(str3, str3_not), s21_strcspn(str3, str3_not));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str1[] = "0123456789";
  char str1_in[] = "987";

  char str2[] = "abced";
  char str2_in[] = "ecd";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";
  char str3_in2[] = "ZYX";

  ck_assert_str_eq(strpbrk(str1, str1_in), s21_strpbrk(str1, str1_in));
  ck_assert_str_eq(strpbrk(str2, str2_in), s21_strpbrk(str2, str2_in));
  ck_assert_str_eq(strpbrk(str3, str3_in), s21_strpbrk(str3, str3_in));
  ck_assert_str_eq(strpbrk(str3, str3_in2), s21_strpbrk(str3, str3_in2));
}
END_TEST

START_TEST(s21_strstr_test) {
  char str1[] = "0123456789";
  char str1_in[] = "789";

  char str2[] = "abced";
  char str2_in[] = "d";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";

  char str4[] = "0123456789";
  char str4_in[] = "345";

  ck_assert_str_eq(strstr(str1, str1_in), s21_strstr(str1, str1_in));
  ck_assert_str_eq(strstr(str2, str2_in), s21_strstr(str2, str2_in));
  ck_assert_str_eq(strstr(str3, str3_in), s21_strstr(str3, str3_in));
  ck_assert_str_eq(strstr(str4, str4_in), s21_strstr(str4, str4_in));
}
END_TEST

START_TEST(s21_to_upper_test) {
  char str1[] = "alexey, you are an idiot, ok?";

  char *str1_upper = s21_to_upper(str1);

  if (str1_upper) {
    ck_assert_str_eq("ALEXEY, YOU ARE AN IDIOT, OK?", str1_upper);
  }
  free(str1_upper);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char str1[] = "ALEXEY, YOU ARE AN IDIOT, OK?";

  char *str1_lower = s21_to_lower(str1);

  if (str1_lower) {
    ck_assert_str_eq("alexey, you are an idiot, ok?", str1_lower);
  }
  free(str1_lower);
}
END_TEST

START_TEST(s21_memset_test) {
  char str1[] = "0123456789";

  for (s21_size_t i = 65; i < 90; i++) {
    ck_assert_str_eq(memset(str1, i, s21_strlen(str1)),
                     s21_memset(str1, i, s21_strlen(str1)));
  }

  char str2[] = "abcdefghijklmnopqrstuvwxyzABCABCABC";
  s21_size_t j = 3;
  for (s21_size_t i = 97; i < 122; i++) {
    ck_assert_str_eq(memset(str2, i, j), s21_memset(str2, i, j));
    j++;
  }
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "kek@lol@arbidol";
  char str1_delim[] = "@";

  char str2[] = "alexey/dog/snoop";
  char str2_delim[] = "/";

  char str3[] = "i&love&school&21";
  char str3_delim[] = "&";

  char str4[] = "^_^i^_^hate^_^strtok^_^!^_^";
  char str4_delim[] = "^_^";

  char str5[] = ".A...A...A...A.";
  char str5_delim[] = ".";

  char str6[] = "12345";
  char str6_delim[] = "1234";

  char str7[] = "12345";
  char str7_delim[] = "\0";

  char str8[] = "12345";
  char str8_delim[] = "?";

  char str9[] = "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z";
  char str9_delim[] = ",";
  char *parts = s21_strtok(str9, str9_delim);
  while (parts) {
    ck_assert_str_eq(strtok(str9, str9_delim), s21_strtok(str9, str9_delim));
    parts = s21_strtok(S21_NULL, str9_delim);
  }

  ck_assert_str_eq(strtok(str1, str1_delim), s21_strtok(str1, str1_delim));
  ck_assert_str_eq(strtok(str2, str2_delim), s21_strtok(str2, str2_delim));
  ck_assert_str_eq(strtok(str3, str3_delim), s21_strtok(str3, str3_delim));
  ck_assert_str_eq(strtok(str4, str4_delim), s21_strtok(str4, str4_delim));
  ck_assert_str_eq(strtok(str5, str5_delim), s21_strtok(str5, str5_delim));
  ck_assert_str_eq(strtok(str6, str6_delim), s21_strtok(str6, str6_delim));
  ck_assert_str_eq(strtok(str7, str7_delim), s21_strtok(str7, str7_delim));
  ck_assert_str_eq(strtok(str8, str8_delim), s21_strtok(str8, str8_delim));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char str1[] = "0123456789";
  char str1_cmp[] = "0123456789";

  char str2[] = "abAdefghijklmnopqrstuvwxyz";
  char str2_cmp[] = "abAdefghijklmnopqrstuvwxyz";

  char str3[] = "12345";
  char str3_cmp[] = "54321";

  char str4[] = "ABCDE";
  char str4_cmp[] = "EDCBA";

  int originalTest1 = memcmp(str1, str1_cmp, strlen(str1)) > 0 ? 1 : -1;
  int myTest1 = s21_memcmp(str1, str1_cmp, s21_strlen(str1)) > 0 ? 1 : -1;

  int originalTest2 = memcmp(str2, str2_cmp, strlen(str2)) > 0 ? 1 : -1;
  int myTest2 = s21_memcmp(str2, str2_cmp, s21_strlen(str2)) > 0 ? 1 : -1;

  int originalTest3 = memcmp(str3, str3_cmp, strlen(str3)) > 0 ? 1 : -1;
  int myTest3 = s21_memcmp(str3, str3_cmp, s21_strlen(str3)) > 0 ? 1 : -1;

  int originalTest4 = memcmp(str4, str4_cmp, strlen(str4)) > 0 ? 1 : -1;
  int myTest4 = s21_memcmp(str4, str4_cmp, s21_strlen(str4)) > 0 ? 1 : -1;

  ck_assert_int_eq(originalTest1, myTest1);
  ck_assert_int_eq(originalTest2, myTest2);
  ck_assert_int_eq(originalTest3, myTest3);
  ck_assert_int_eq(originalTest4, myTest4);
}
END_TEST

START_TEST(s21_test_trim) {
  char s1[30] = "-?hello, world!";
  char s3[] = "!?-";
  char s4[] = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_str_eq(s4, s2);
  free(s2);
}
END_TEST

START_TEST(s21_test_insert) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_str_eq(s4, s2);
  free(s2);
}
END_TEST

START_TEST(sprintf_1_signed) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple value %d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Test %d Test %d";
  int val = 012;
  int val2 = -017;
  int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%ld Test %ld Test %hd GOD %hd";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  short int val3 = 22600;
  short val4 = -120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%3d Test %5d Test %10d";
  int val = -3015;
  int val2 = -11234;
  int val3 = -99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5d Test %.23d Test %3.d TEST %.d %.6d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -38;
  int val5 = -100;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5d Test %-.8d Test %-7d TEST %-.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %0.d Test %0.0d TEST %0d GOD %.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  int val5 = -0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%d Test %3.d Test %5.7d TEST %10d %#d %-d %+d %.d % .d";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val,
                  val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
  int val = -32;
  int val2 = -8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d GOD %+.d";
  int val = -32;
  int val2 = -8899;
  int val3 = 91918;
  int val4 = -32311;
  int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%#d Test %#3d Test %#5.7d TEST %#.7d Oof %#.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = 32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %06d Test %05.7d TEST %0.7d Oof %0.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%*d Test %-*d Test %*.*d TEST %.*d";
  int val = 32;
  int val2 = 8899;
  int val3 = -919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%- d Test %- 15d sdasda %- 15d sdsad %- d";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_octal) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %o Test";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %o Test %o";
  int val = 012;
  int val2 = 017;
  int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %o Test %o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%lo Test %lo Test %ho GOD %ho";
  long int val = 3088675747373646;
  unsigned long int val2 = 33030030303;
  unsigned short int val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%3o Test %5o Test %10o";
  int val = 3015;
  int val2 = 01234;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5o Test %.23o Test %3.o TEST %.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 38;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5o Test %-.8o Test %-7o TEST %-.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%0o Test %0.o Test %0.0o TEST %0o GOD %.o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%+o Test %+3.o Test %+5.7o TEST %+10o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%o Test %3.o Test %5.7o TEST %10o %o %-o %+o %.o % .o";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "% o Test % 3.o Test % 5.7o TEST % 10o GOD %.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%+o Test %+3.o Test %+5.7o TEST %+10o GOD %+.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%0o Test %06o Test %05.7o TEST %0.7o Oof %0.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%*o Test %-*o Test %*.*o TEST %.*o";
  int val = 32;
  int val2 = 8899;
  int val3 = 919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_octal) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%o";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%- o Test %- 15o sdasda %- 15o sdsad %- o";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_short) {
  char str1[1000];
  char str2[1000];

  char *format = "%hd";
  short int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_unsigned) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %u Test";
  unsigned int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 012;
  unsigned int val2 = 017;
  unsigned int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%lu Test %lu Test %hu GOD %hu";
  long unsigned int val = 3088675747373646;
  long unsigned val2 = 33030030303;
  unsigned short val3 = 22600;
  unsigned short val4 = 120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_unsigned) {
  char str1[100];
  char str2[100];
  char *str3 = "%3u Test %5u Test %10u";
  unsigned int val = 3015;
  unsigned int val2 = 01234;
  unsigned int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5u Test %.23u Test %3.u TEST %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 38;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5u Test %-.8u Test %-7u TEST %-.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %0.u Test %0.0u TEST %0u GOD %.u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  unsigned int val5 = 0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u";
  unsigned int val = 3015;
  unsigned int val2 = 712;
  unsigned int val3 = 99;
  unsigned int val4 = 2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%u Test %3.u Test %5.7u TEST %10u %#u %-u %+u %.u % .u";
  unsigned int val = 0;
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "% u Test % 3.u Test % 5.7u TEST % 10u GOD %.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %06u Test %05.7u TEST %0.7u Ouf %0.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_string) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %s Test";
  char *val = "Why am I here?!";
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "I'm so tired";
  char *val2 = "Who invented this?";
  char *val3 = "This project gave me hemmoroids";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_string) {
  char str1[100];
  char str2[100];
  char *str3 = "%s Test %s Test %s";
  char *val = "Don't need this test";
  char *val2 = "Just for the kicks";
  char *val3 = "Lol";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%3s Test %5s Test %10s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore";
  char *val3 = "PPAP";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5s Test %.23s Test %3.s TEST %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5s Test %-.8s Test %-7s TEST %-.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%0s Test %0.s Test %0.0s TEST %0s GOD %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s Test %+3.s Test %5.7s TEST %10s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "abcd";
  char *val4 = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_string) {
  char str1[200];
  char str2[200];
  char *str3 = "% s Test % 3.s Test % 5.7s TEST % 10s GOD %.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%+s Test %+3.s Test %+5.7s TEST %+10s GOD %+.s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_string) {
  char str1[200];
  char str2[200];
  char *str3 = "%*s Test %-*s Test %*.*s TEST %.*s";
  char *val = "WHAT IS THIS";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int c = 17;
  int d = 66;
  int e = 124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = -6;
  int b = -10;
  int c = -17;
  int d = -66;
  int e = -124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%#c Test %#c Test %#c Test %#c Test %#c";
  ck_assert_int_eq(sprintf(str1, str3, ' ', 'n', '5', '%', '\\'),
                   s21_sprintf(str2, str3, ' ', 'n', '5', '%', '\\'));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_c) {
  char str1[400];
  char str2[400];
  char *str3 = "%.7c Test % -.7c Test %- 050c Test %- 54c Test %-0188c";
  int a = 45;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                   s21_sprintf(str2, str3, a, a, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprint_string_null) {
  char str1[1000];
  char str2[1000];

  char *format = "%s";
  char *string = NULL;
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float) {
  char str1[1000];
  char str2[1000];

  char *format = "%f";
  double num = 1.9;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%f";
  double zero = 0;
  s21_sprintf(str1, format, zero);
  sprintf(str2, format, zero);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double negative = -0.34834493943;
  s21_sprintf(str1, format, negative);
  sprintf(str2, format, negative);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double_negative) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double num = -10.934;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 18.0f\ntest: %+10.f\ntest: %+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-15.4f!\ntest: %-26.1f!\ntest: %-18.0f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.13f!\ntest: %26.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7f!\ntest: %10.15f!\ntest: %25.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_percent) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%%Test %o Test";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_percent) {
  char str1[100];
  char str2[100];
  char *str3 = "Test %o Tes%%%%t %o";
  int val = 012;
  int val2 = 017;
  ck_assert_int_eq(sprintf(str1, str3, val, val2),
                   s21_sprintf(str2, str3, val, val2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_percent) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Te%%st %o Test %o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_strerror_test);
  tcase_add_test(tc1_1, s21_memchr_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_to_upper_test);
  tcase_add_test(tc1_1, s21_to_lower_test);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_strtok_test);
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_test_trim);
  tcase_add_test(tc1_1, s21_test_insert);

  tcase_add_test(tc1_1, sprintf_1_signed);
  tcase_add_test(tc1_1, sprintf_2_signed);
  tcase_add_test(tc1_1, sprintf_3_signed);
  tcase_add_test(tc1_1, sprintf_4_signed);
  tcase_add_test(tc1_1, sprintf_5_signed);
  tcase_add_test(tc1_1, sprintf_6_signed);
  tcase_add_test(tc1_1, sprintf_7_signed);
  tcase_add_test(tc1_1, sprintf_8_signed);
  tcase_add_test(tc1_1, sprintf_9_signed);
  tcase_add_test(tc1_1, sprintf_10_signed);
  tcase_add_test(tc1_1, sprintf_11_signed);
  tcase_add_test(tc1_1, sprintf_12_signed);
  tcase_add_test(tc1_1, sprintf_13_signed);
  tcase_add_test(tc1_1, sprintf_14_signed);
  tcase_add_test(tc1_1, sprintf_15_signed);
  tcase_add_test(tc1_1, sprintf_1_octal);
  tcase_add_test(tc1_1, sprintf_1_octal);
  tcase_add_test(tc1_1, sprintf_2_octal);
  tcase_add_test(tc1_1, sprintf_3_octal);
  tcase_add_test(tc1_1, sprintf_4_octal);
  tcase_add_test(tc1_1, sprintf_5_octal);
  tcase_add_test(tc1_1, sprintf_6_octal);
  tcase_add_test(tc1_1, sprintf_7_octal);
  tcase_add_test(tc1_1, sprintf_8_octal);
  tcase_add_test(tc1_1, sprintf_9_octal);
  tcase_add_test(tc1_1, sprintf_10_octal);
  tcase_add_test(tc1_1, sprintf_11_octal);
  tcase_add_test(tc1_1, sprintf_12_octal);
  tcase_add_test(tc1_1, sprintf_14_octal);
  tcase_add_test(tc1_1, sprintf_15_octal);
  tcase_add_test(tc1_1, sprintf_16_octal);
  tcase_add_test(tc1_1, sprintf_17_octal);
  tcase_add_test(tc1_1, sprintf_octal_short);
  tcase_add_test(tc1_1, sprintf_1_unsigned);
  tcase_add_test(tc1_1, sprintf_2_unsigned);
  tcase_add_test(tc1_1, sprintf_3_unsigned);
  tcase_add_test(tc1_1, sprintf_4_unsigned);
  tcase_add_test(tc1_1, sprintf_5_unsigned);
  tcase_add_test(tc1_1, sprintf_6_unsigned);
  tcase_add_test(tc1_1, sprintf_7_unsigned);
  tcase_add_test(tc1_1, sprintf_8_unsigned);
  tcase_add_test(tc1_1, sprintf_9_unsigned);
  tcase_add_test(tc1_1, sprintf_10_unsigned);
  tcase_add_test(tc1_1, sprintf_11_unsigned);
  tcase_add_test(tc1_1, sprintf_12_unsigned);
  tcase_add_test(tc1_1, sprintf_14_unsigned);
  tcase_add_test(tc1_1, sprintf_1_string);
  tcase_add_test(tc1_1, sprintf_2_string);
  tcase_add_test(tc1_1, sprintf_3_string);
  tcase_add_test(tc1_1, sprintf_5_string);
  tcase_add_test(tc1_1, sprintf_6_string);
  tcase_add_test(tc1_1, sprintf_7_string);
  tcase_add_test(tc1_1, sprintf_8_string);
  tcase_add_test(tc1_1, sprintf_9_string);
  tcase_add_test(tc1_1, sprintf_11_string);
  tcase_add_test(tc1_1, sprintf_12_string);
  tcase_add_test(tc1_1, sprintf_15_string);
  tcase_add_test(tc1_1, sprintf_1_c);
  tcase_add_test(tc1_1, sprintf_2_c);
  tcase_add_test(tc1_1, sprintf_3_c);
  tcase_add_test(tc1_1, sprintf_4_c);
  tcase_add_test(tc1_1, sprintf_5_c);
  tcase_add_test(tc1_1, sprintf_6_c);
  tcase_add_test(tc1_1, sprintf_1_c);
  tcase_add_test(tc1_1, sprintf_1_c);
  tcase_add_test(tc1_1, sprint_string_null);
  tcase_add_test(tc1_1, sprintf_float);
  tcase_add_test(tc1_1, sprintf_float_zero);
  tcase_add_test(tc1_1, sprintf_double);
  tcase_add_test(tc1_1, sprintf_double_negative);
  tcase_add_test(tc1_1, sprintf_11_f);
  tcase_add_test(tc1_1, sprintf_14_f);
  tcase_add_test(tc1_1, sprintf_16_f);
  tcase_add_test(tc1_1, sprintf_17_f);
  tcase_add_test(tc1_1, sprintf_1_percent);
  tcase_add_test(tc1_1, sprintf_2_percent);
  tcase_add_test(tc1_1, sprintf_3_percent);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
