#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("Hello world!"), strlen("Hello world!"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));

  char long_str[1001];
  memset(long_str, 'a', 1000);
  long_str[1000] = '\0';
  ck_assert_int_eq(s21_strlen(long_str), strlen(long_str));
}
END_TEST

START_TEST(test_s21_strcspn) {
  ck_assert_int_eq(s21_strcspn("0123456789", "9876"),
                   strcspn("0123456789", "9876"));
  ck_assert_int_eq(s21_strcspn("0126789345", "9876"),
                   strcspn("0126789345", "9876"));
  ck_assert_int_eq(s21_strcspn("abacada", "d"), strcspn("abacada", "d"));
  char str[] = "Hello my friend,\0 how long can I do this project?";
  ck_assert_int_eq(s21_strcspn(str, "this"), strcspn(str, "this"));
  ck_assert_int_eq(s21_strcspn(str, "\0"), strcspn(str, "\0"));
  ck_assert_int_eq(s21_strcspn("", "this"), strcspn("", "this"));
  ck_assert_int_eq(s21_strcspn("this", str), strcspn("this", str));
  ck_assert_int_eq(s21_strcspn("\0", str), strcspn("\0", str));
  ck_assert_int_eq(s21_strcspn(str, ""), strcspn(str, ""));
}
END_TEST

START_TEST(test_s21_strstr) {
  ck_assert_ptr_eq(s21_strstr("abc", "a"), strstr("abc", "a"));
  ck_assert_ptr_eq(s21_strstr("abc", "b"), strstr("abc", "b"));
  ck_assert_ptr_eq(s21_strstr("abc", "c"), strstr("abc", "c"));
  ck_assert_ptr_eq(s21_strstr("abc", ""), strstr("abc", ""));
  ck_assert_ptr_eq(s21_strstr("", "abc"), strstr("", "abc"));
  ck_assert_ptr_eq(s21_strstr("abc", "qwe"), strstr("abc", "qwe"));
  ck_assert_ptr_eq(s21_strstr("hello bob?", "b"), strstr("hello bob?", "b"));
  ck_assert_ptr_eq(s21_strstr("hello bob? hello ron.", "hello"),
                   strstr("hello bob? hello ron.", "hello"));
  ck_assert_ptr_eq(s21_strstr("hello bob?\0 hello ron.", "ron"),
                   strstr("hello bob?\0 hello ron.", "ron"));
}
END_TEST

START_TEST(test_s21_memchr) {
  ck_assert_ptr_eq(s21_memchr("abc", 'a', 3), memchr("abc", 'a', 3));
  ck_assert_ptr_eq(s21_memchr("abc", 'b', 3), memchr("abc", 'b', 3));
  ck_assert_ptr_eq(s21_memchr("abc", 'c', 3), memchr("abc", 'c', 3));
  ck_assert_ptr_eq(s21_memchr("abc", 'q', 3), memchr("abc", 'q', 3));
  ck_assert_ptr_eq(s21_memchr("abc", 'c', 0), memchr("abc", 'c', 0));
  ck_assert_ptr_eq(s21_memchr("abc", ' ', 3), memchr("abc", ' ', 3));
  ck_assert_ptr_eq(s21_memchr("abc\0 pok", 'p', 3),
                   memchr("abc\0 pok", 'p', 3));
  ck_assert_ptr_eq(s21_memchr("abc\0 pok", 'p', 8),
                   memchr("abc\0 pok", 'p', 8));
}
END_TEST

START_TEST(test_s21_memcmp) {
  ck_assert_int_eq(s21_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));
  ck_assert_int_eq(s21_memcmp("abc", "a", 1), memcmp("abc", "a", 1));
  ck_assert_int_eq(s21_memcmp("abc", "b", 1), memcmp("abc", "b", 1));
  ck_assert_int_eq(s21_memcmp("qwertylog", "qwerta", 3),
                   memcmp("qwertylog", "qwerta", 3));
  ck_assert_int_eq(s21_memcmp("qwertylog", "qwerta", 0),
                   memcmp("qwertylog", "qwerta", 0));
  ck_assert_int_eq(s21_memcmp("", "qwerta", 0), memcmp("", "qwerta", 0));
  ck_assert_int_eq(s21_memcmp("", "", 0), memcmp("", "", 0));
  ck_assert_int_eq(s21_memcmp("", "", 5), memcmp("", "", 5));
}
END_TEST

START_TEST(test_s21_strncmp) {
  ck_assert_int_eq(s21_strncmp("", "", 0), strncmp("", "", 0));
  ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
  ck_assert_int_eq(s21_strncmp("abc", "a", 0), strncmp("abc", "a", 0));
  ck_assert_int_eq(s21_strncmp("abc", "b", 3), strncmp("abc", "b", 3));
  ck_assert_int_eq(s21_strncmp("qwertylog", "qwerta", 0),
                   strncmp("qwertylog", "qwerta", 0));
  ck_assert_int_eq(s21_strncmp("qwertylog", "qwerta", 3),
                   strncmp("qwertylog", "qwerta", 3));
  ck_assert_int_eq(s21_strncmp("", "qwerta", 0), strncmp("", "qwerta", 0));
  ck_assert_int_eq(s21_strncmp("abc\0c", "abc\0e", 5),
                   strncmp("abc\0c", "abc\0e", 5));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char dest1[4] = "abc";
  char src1[4] = "abc";
  ck_assert_str_eq(s21_memcpy(dest1, src1, 3), memcpy(dest1, src1, 3));

  char dest2[4] = "abc";
  char src2[2] = "a";
  ck_assert_str_eq(s21_memcpy(dest2, src2, 2), memcpy(dest2, src2, 2));

  char dest3[4] = "abc";
  char src3[2] = "b";
  ck_assert_str_eq(s21_memcpy(dest3, src3, 2), memcpy(dest3, src3, 2));

  char dest4[4] = "abc";
  char src4[2] = "c";
  ck_assert_str_eq(s21_memcpy(dest4, src4, 2), memcpy(dest4, src4, 2));

  char dest5[4] = "abc";
  char src5[4] = "def";
  ck_assert_str_eq(s21_memcpy(dest5, src5, 0), memcpy(dest5, src5, 0));

  char dest6[4] = "abc";
  char src6[1] = "";
  ck_assert_str_eq(s21_memcpy(dest6, src6, 1), memcpy(dest6, src6, 1));

  char data[5] = "abcde";
  ck_assert_str_eq(s21_memcpy(data + 2, data, 3), memcpy(data + 2, data, 3));
}
END_TEST

START_TEST(test_s21_memset) {
#if defined(__APPLE__)
  ck_assert_ptr_eq(s21_memset(0, 0, 0), memset(0, 0, 0));

  char dest1[4] = "abc";
  char res1[4] = "abc";
  ck_assert_str_eq(s21_memset(dest1, 'e', 0), memset(res1, 'e', 0));

  char str1[30] = "qwerty";
  char str2[30] = "qwerty";
  ck_assert_str_eq(s21_memset(str1, 'e', 0), memset(str2, 'e', 0));

#endif
  char str3[30] = "qwerty";
  char str4[30] = "qwerty";
  ck_assert_str_eq(s21_memset(str3, 'e', 10), memset(str4, 'e', 10));

  char str5[30] = "a\n\0";
  char str6[30] = "a\n\0";
  ck_assert_str_eq(s21_memset(str5, ' ', 5), memset(str6, ' ', 5));

  char str7[30] = "\0";
  char str8[30] = "\0";
  ck_assert_str_eq(s21_memset(str7, 'e', 1), memset(str8, 'e', 1));
}
END_TEST

START_TEST(test_s21_strncat) {
  char str1[50] = "";
  char str2[50] = "";
  ck_assert_str_eq(s21_strncat(str1, "   ", 3), s21_strncat(str2, "   ", 3));

  char str3[50] = "";
  char str4[50] = "";
  ck_assert_str_eq(s21_strncat(str3, "Hello World\n\0", 3),
                   s21_strncat(str4, "Hello World\n\0", 3));

  char str5[50] = "";
  char str6[50] = "";
  ck_assert_str_eq(s21_strncat(str5, "Hello World\n\0", 12),
                   s21_strncat(str6, "Hello World\n\0", 12));

  char str11[50] = "";
  char str12[50] = "";
  ck_assert_str_eq(s21_strncat(str11, "\0", 1), s21_strncat(str12, "\0", 1));

  char str7[50] = "\0";
  char str8[50] = "\0";
  ck_assert_str_eq(s21_strncat(str7, "a\n\0", 2),
                   s21_strncat(str8, "a\n\0", 2));

  char str9[50] = "qwerty";
  char str10[50] = "qwerty";
  ck_assert_str_eq(s21_strncat(str9, "\n\n\0", 2),
                   s21_strncat(str10, "\n\n\0", 2));
}
END_TEST

START_TEST(test_s21_strchr) {
  ck_assert_ptr_eq(s21_strchr("cbabc", 'a'), strchr("cbabc", 'a'));
  ck_assert_ptr_eq(s21_strchr("cbabc", 'c'), strchr("cbabc", 'c'));
  ck_assert_ptr_eq(s21_strchr("nbabc", 'c'), strchr("nbabc", 'c'));
  ck_assert_ptr_eq(s21_strchr("", 'c'), strchr("", 'c'));
  ck_assert_ptr_eq(s21_strchr("Bob\0 Coll", 'c'), strchr("Bob\0 Coll", 'c'));
  ck_assert_ptr_eq(s21_strchr("banana", 'a'), strchr("banana", 'a'));
}
END_TEST

START_TEST(test_s21_strrchr) {
  ck_assert_ptr_eq(s21_strrchr("cbabc", 'a'), strrchr("cbabc", 'a'));
  ck_assert_ptr_eq(s21_strrchr("cbabc", 'c'), strrchr("cbabc", 'c'));
  ck_assert_ptr_eq(s21_strrchr("ncbabcp ", 'c'), strrchr("ncbabcp ", 'c'));
  ck_assert_ptr_eq(s21_strrchr("", 'c'), strchr("", 'c'));
  ck_assert_ptr_eq(s21_strrchr("Bob\0 Coll", 'c'), strrchr("Bob\0 Coll", 'c'));
  ck_assert_ptr_eq(s21_strrchr("Bob\0 Coll", '\0'),
                   strrchr("Bob\0 Coll", '\0'));
  ck_assert_ptr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  ck_assert_ptr_eq(s21_strpbrk("cbabc", "AdoN"), strpbrk("cbabc", "AdoN"));
  ck_assert_ptr_eq(s21_strpbrk("cbabc", "Max"), strpbrk("cbabc", "Max"));
  ck_assert_ptr_eq(s21_strpbrk("ncba bcp ", " "), strpbrk("ncba bcp ", " "));
  ck_assert_ptr_eq(s21_strpbrk("", "t"), strpbrk("", "t"));
  ck_assert_ptr_eq(s21_strpbrk("Bob\0 Coll", "Ll"),
                   strpbrk("Bob\0 Coll", "Ll"));
  ck_assert_ptr_eq(s21_strpbrk("Bob\0 Coll", "OLl"),
                   strpbrk("Bob\0 Coll", "OLl"));
}
END_TEST

START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(-56), strerror(-56));
  ck_assert_str_eq(s21_strerror(5), strerror(5));
  ck_assert_str_eq(s21_strerror(124), strerror(124));
  ck_assert_str_eq(s21_strerror(500), strerror(500));
  ck_assert_str_eq(s21_strerror(88), strerror(88));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1[50] = "Hello world\n\0";
  ck_assert_ptr_eq(s21_strtok(str1, "\n\0"), strtok(str1, "\n\0"));
  ck_assert_str_eq(s21_strtok(str1, "\n\0"), strtok(str1, "\n\0"));

  char str3[50] = "a\n\0";
  ck_assert_str_eq(s21_strtok(str3, "\n\0"), strtok(str3, "\n\0"));

  ck_assert_ptr_eq(s21_strtok(s21_NULL, "\n\0"), strtok(s21_NULL, "\n\0"));

  char str5[50] = "q w e r t y";
  ck_assert_str_eq(s21_strtok(str5, "123"), strtok(str5, "123"));

  char str7[50] = "\n\0";
  ck_assert_str_eq(s21_strtok(str7, ""), strtok(str7, ""));

  char str9[50] = "Hello world\n\0";

  ck_assert_str_eq(s21_strtok(str9, ""), strtok(str9, ""));

  char str2[50] = "Hello::world::!";
  char str4[50] = "Hello::world::!";
  char *delims = " :";
  char *s21_token = s21_strtok(str2, delims);
  char *token = strtok(str4, delims);
  while (s21_token != NULL && token != NULL) {
    ck_assert_str_eq(s21_token, token);
    s21_token = s21_strtok(NULL, delims);
    token = strtok(NULL, delims);
  }
  ck_assert_ptr_eq(s21_token, token);
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest[100] = {};
  char dest_origin[100] = {};
  char src[] = "hello";

  ck_assert_str_eq(s21_strncpy(dest, src, 3), strncpy(dest_origin, src, 3));
  ck_assert_str_eq(s21_strncpy(dest, "h\0el\0lo", 3),
                   strncpy(dest_origin, "h\0el\0lo", 3));
  ck_assert_str_eq(s21_strncpy(dest, "hel\0lo", 7),
                   strncpy(dest_origin, "hel\0lo", 7));

  char src_2[] = "Hello my friend,\0 how long can I do this project?";
  ck_assert_str_eq(s21_strncpy(dest, src_2, 5), strncpy(dest_origin, src_2, 5));
  ck_assert_str_eq(s21_strncpy(dest, src_2, s21_strlen(src_2)),
                   strncpy(dest_origin, src_2, s21_strlen(src_2)));
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str1[] = "HELLO";
  char *result1 = s21_to_lower(str1);
  ck_assert_str_eq(result1, "hello");
  free(result1);

  char str2[] = "HeLLo WoRLd!";
  char *result2 = s21_to_lower(str2);
  ck_assert_str_eq(result2, "hello world!");
  free(result2);

  char str3[] = "12345";
  char *result3 = s21_to_lower(str3);
  ck_assert_str_eq(result3, "12345");
  free(result3);

  char *result5 = s21_to_lower(NULL);
  ck_assert_ptr_eq(result5, NULL);

  char str[] = "   Area  Without  Space   ";
  char exp[] = "   area  without  space   ";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, exp);
  if (got) free(got);

  char str_3[] = "   ";
  char exp_3[] = "   ";
  char *got_3 = s21_to_lower(str_3);
  ck_assert_str_eq(got_3, exp_3);
  if (got_3) free(got_3);

  char str_4[] = "";
  char exp_4[] = "";
  char *got_4 = s21_to_lower(str_4);
  ck_assert_str_eq(got_4, exp_4);
  if (got_4) free(got_4);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str1[] = "hello";
  char *result1 = s21_to_upper(str1);
  ck_assert_str_eq(result1, "HELLO");
  free(result1);

  char str2[] = "HeLLo WoRLd!";
  char *result2 = s21_to_upper(str2);
  ck_assert_str_eq(result2, "HELLO WORLD!");
  free(result2);

  char str3[] = "12345";
  char *result3 = s21_to_upper(str3);
  ck_assert_str_eq(result3, "12345");
  free(result3);

  char *result5 = s21_to_upper(NULL);
  ck_assert_ptr_eq(result5, NULL);

  char str[] = "   Area  Without  Space   ";
  char exp[] = "   AREA  WITHOUT  SPACE   ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, exp);
  if (got) free(got);

  char str_3[] = "   ";
  char exp_3[] = "   ";
  char *got_3 = s21_to_upper(str_3);
  ck_assert_str_eq(got_3, exp_3);
  if (got_3) free(got_3);

  char str_4[] = "";
  char exp_4[] = "";
  char *got_4 = s21_to_upper(str_4);
  ck_assert_str_eq(got_4, exp_4);
  if (got_4) free(got_4);
}
END_TEST

START_TEST(test_s21_trim) {
  char str1[] = "   hello   ";
  char trim_chars1[] = " ";
  char *result1 = s21_trim(str1, trim_chars1);
  ck_assert_str_eq(result1, "hello");
  free(result1);

  char str2[] = "**@@hello@@**";
  char trim_chars2[] = "*@";
  char *result2 = s21_trim(str2, trim_chars2);
  ck_assert_str_eq(result2, "hello");
  free(result2);

  char str3[] = "---hello world---";
  char trim_chars3[] = "-";
  char *result3 = s21_trim(str3, trim_chars3);
  ck_assert_str_eq(result3, "hello world");
  free(result3);

  char str4[] = "hello";
  char trim_chars4[] = "@";
  char *result4 = s21_trim(str4, trim_chars4);
  ck_assert_str_eq(result4, "hello");
  free(result4);

  char *result5 = s21_trim(s21_NULL, " ");
  ck_assert_ptr_eq(result5, s21_NULL);

  char *result7 = s21_trim(" ", s21_NULL);
  ck_assert_ptr_eq(result7, s21_NULL);

  char str6[] = "";
  char trim_chars6[] = " ";
  char *result6 = s21_trim(str6, trim_chars6);
  ck_assert_str_eq(result6, "");
  free(result6);
}
END_TEST

START_TEST(test_s21_insert) {
  char str1[] = "Hello, world!";
  char insert1[] = " beautiful";
  char *result1 = s21_insert(str1, insert1, 6);
  ck_assert_str_eq(result1, "Hello, beautiful world!");
  free(result1);

  char str2[] = "Hello, world!";
  char insert2[] = " wonderful";
  char *result2 = s21_insert(str2, insert2, 50);
  ck_assert_ptr_eq(result2, s21_NULL);
  free(result2);

  char str3[] = "Hello, world!";
  char insert3[] = "!";
  char *result3 = s21_insert(str3, insert3, 13);
  ck_assert_str_eq(result3, "Hello, world!!");
  free(result3);
}
END_TEST

START_TEST(test_sprintf_c) {
  char buffer[100];
  char buffer_orig[100];
  char c = '#';
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %c - da", c),
                   sprintf(buffer_orig, "Yes, %c - da", c));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10c - da", c),
                   sprintf(buffer_orig, "Yes, %10c - da", c));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10c - da", c),
                   sprintf(buffer_orig, "Yes, %-10c - da", c));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_d) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %d - da", d),
                   sprintf(buffer_orig, "Yes, %d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_f) {
  char buffer[100];
  char buffer_orig[100];
  float f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %f - da", f),
                   sprintf(buffer_orig, "Yes, %f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);

  char buffer1[100];
  char buffer_orig1[100];
  float f1 = 0.0;
  ck_assert_int_eq(s21_sprintf(buffer1, "Zero: %f", f1),
                   sprintf(buffer_orig1, "Zero: %f", f1));
  ck_assert_str_eq(buffer1, buffer_orig1);

  char buffer2[100];
  char buffer_orig2[100];
  float f2 = -123.456;
  ck_assert_int_eq(s21_sprintf(buffer2, "Negative: %f", f2),
                   sprintf(buffer_orig2, "Negative: %f", f2));
  ck_assert_str_eq(buffer2, buffer_orig2);

  char buffer3[100];
  char buffer_orig3[100];
  float f3 = 12345678.12345678;
  ck_assert_int_eq(s21_sprintf(buffer3, "Large: %f", f3),
                   sprintf(buffer_orig3, "Large: %f", f3));
  ck_assert_str_eq(buffer3, buffer_orig3);

  char buffer4[100];
  char buffer_orig4[100];
  float f4 = 0.000123456;
  ck_assert_int_eq(s21_sprintf(buffer4, "Small: %f", f4),
                   sprintf(buffer_orig4, "Small: %f", f4));
  ck_assert_str_eq(buffer4, buffer_orig4);

  char buffer5[100];
  char buffer_orig5[100];
  float f5 = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer5, "Precision: %.2f", f5),
                   sprintf(buffer_orig5, "Precision: %.2f", f5));
  ck_assert_str_eq(buffer5, buffer_orig5);

  char buffer6[100];
  char buffer_orig6[100];
  float f6 = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer6, "Width: %10f", f6),
                   sprintf(buffer_orig6, "Width: %10f", f6));
  ck_assert_str_eq(buffer6, buffer_orig6);

  char buffer7[100];
  char buffer_orig7[100];
  float f7 = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer7, "Width & Precision: %10.2f", f7),
                   sprintf(buffer_orig7, "Width & Precision: %10.2f", f7));
  ck_assert_str_eq(buffer7, buffer_orig7);

  char buffer8[100];
  char buffer_orig8[100];
  float f8 = -123.456;
  ck_assert_int_eq(s21_sprintf(buffer8, "Neg. Width & Prec: %10.2f", f8),
                   sprintf(buffer_orig8, "Neg. Width & Prec: %10.2f", f8));
  ck_assert_str_eq(buffer8, buffer_orig8);

  char buffer9[100];
  char buffer_orig9[100];
  float f9 = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer9, "Zero pad: %010.2f", f9),
                   sprintf(buffer_orig9, "Zero pad: %010.2f", f9));
  ck_assert_str_eq(buffer9, buffer_orig9);

  char buffer0[100];
  char buffer_orig0[100];
  float f0 = 1.23e-6;
  ck_assert_int_eq(s21_sprintf(buffer0, "Exponent: %f", f0),
                   sprintf(buffer_orig0, "Exponent: %f", f0));
  ck_assert_str_eq(buffer0, buffer_orig0);
  /*
    char buffer11[100];
    char buffer_orig11[100];
    double f11 = 456.123;
    ck_assert_int_eq(s21_sprintf(buffer11, "Yes, %+010d - da", f11),
                     sprintf(buffer_orig11, "Yes, %+010d - da", f11));
    ck_assert_str_eq(buffer11, buffer_orig11);

    char buffer12[100];
    char buffer_orig12[100];
    double f12 = 456.000;
    ck_assert_int_eq(s21_sprintf(buffer12, "Yes, %-+10d - da", f12),
                     sprintf(buffer_orig12, "Yes, %-+10d - da", f12));
    ck_assert_str_eq(buffer12, buffer_orig12);
  */
  char buffer13[100];
  char buffer_orig13[100];
  double f13 = 456.6;
  ck_assert_int_eq(s21_sprintf(buffer13, "Yes, % 010f - da", f13),
                   sprintf(buffer_orig13, "Yes, % 010f - da", f13));
  ck_assert_str_eq(buffer13, buffer_orig13);

  char buffer14[100];
  char buffer_orig14[100];
  double f14 = 456.123;
  ck_assert_int_eq(s21_sprintf(buffer14, "Yes, %#010f - da", f14),
                   sprintf(buffer_orig14, "Yes, %#010f - da", f14));
  ck_assert_str_eq(buffer14, buffer_orig14);

  char buffer15[100];
  char buffer_orig15[100];
  double f15 = 456;
  ck_assert_int_eq(s21_sprintf(buffer15, "Yes, %-+*f - da", 10, f15),
                   sprintf(buffer_orig15, "Yes, %-+*f - da", 10, f15));
  ck_assert_str_eq(buffer15, buffer_orig15);
}
END_TEST

START_TEST(test_sprintf_s) {
  char buffer[100];
  char buffer_orig[100];
  char s[] = "Hello";
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %s - da", s),
                   sprintf(buffer_orig, "Yes, %s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10s - da", s),
                   sprintf(buffer_orig, "Yes, %10s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10s - da", s),
                   sprintf(buffer_orig, "Yes, %-10s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10.3s - da", s),
                   sprintf(buffer_orig, "Yes, %10.3s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10.3s - da", ""),
                   sprintf(buffer_orig, "Yes, %10.3s - da", ""));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10.9s - da", s),
                   sprintf(buffer_orig, "Yes, %10.9s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %1.9s - da", s),
                   sprintf(buffer_orig, "Yes, %1.9s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-1.9s - da", s),
                   sprintf(buffer_orig, "Yes, %-1.9s - da", s));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_u) {
  char buffer[100];
  char buffer_orig[100];
  unsigned int u = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %u - da", u),
                   sprintf(buffer_orig, "Yes, %u - da", u));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buffer[100];
  char buffer_orig[100];
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %% - da"),
                   sprintf(buffer_orig, "Yes, %% - da"));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_x) {
  char buffer[100];
  char buffer_orig[100];
  int x = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %x - da", x),
                   sprintf(buffer_orig, "Yes, %x - da", x));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_X) {
  char buffer[100];
  char buffer_orig[100];
  int X = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %X - da", X),
                   sprintf(buffer_orig, "Yes, %X - da", X));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_o) {
  char buffer[100];
  char buffer_orig[100];
  int o = 1245;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %o - da", o),
                   sprintf(buffer_orig, "Yes, %o - da", o));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_p) {
  char buffer[100];
  char buffer_orig[100];
  char *str = "ababa";
  char *p = str + 2;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %p - da", p),
                   sprintf(buffer_orig, "Yes, %p - da", p));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

END_TEST

START_TEST(test_sprintf_width) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10d - da", d),
                   sprintf(buffer_orig, "Yes, %10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_width_star) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %*d - da", 10, d),
                   sprintf(buffer_orig, "Yes, %*d - da", 10, d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_precision) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.2f - da", f),
                   sprintf(buffer_orig, "Yes, %.2f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.*f - da", 2, f),
                   sprintf(buffer_orig, "Yes, %.*f - da", 2, f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_ld) {
  char buffer[100];
  char buffer_orig[100];
  long int l = 123456789012345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %ld - da", l),
                   sprintf(buffer_orig, "Yes, %ld - da", l));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_hd) {
  char buffer[100];
  char buffer_orig[100];
  short int h = 12345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %hd - da", h),
                   sprintf(buffer_orig, "Yes, %hd - da", h));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_lu) {
  char buffer[100];
  char buffer_orig[100];
  long unsigned int l = 123456789012345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %lu - da", l),
                   sprintf(buffer_orig, "Yes, %lu - da", l));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_hu) {
  char buffer[100];
  char buffer_orig[100];
  unsigned int h = 123456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %hu - da", h),
                   sprintf(buffer_orig, "Yes, %hu - da", h));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_length_L) {
  char buffer[100];
  char buffer_orig[100];
  long double L = 12345.6789;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %Lf - da", L),
                   sprintf(buffer_orig, "Yes, %Lf - da", L));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_plus) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %+d - da", d),
                   sprintf(buffer_orig, "Yes, %+d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_minus) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10d - da", d),
                   sprintf(buffer_orig, "Yes, %-10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_space) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, % d - da", d),
                   sprintf(buffer_orig, "Yes, % d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_zero) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %010d - da", d),
                   sprintf(buffer_orig, "Yes, %010d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_flag_hash) {
  char buffer[100];
  char buffer_orig[100];
  int x = 180150001;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#x - da", x),
                   sprintf(buffer_orig, "Yes, %#x - da", x));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_negative_width) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10d - da", d),
                   sprintf(buffer_orig, "Yes, %-10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_negative_precision) {
  char buffer[100];
  char buffer_orig[100];
  double f = 123.456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %.2f - da", f),
                   sprintf(buffer_orig, "Yes, %.2f - da", f));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_negative_length) {
  char buffer[100];
  char buffer_orig[100];
  long int l = 123456789012345;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %ld - da", l),
                   sprintf(buffer_orig, "Yes, %ld - da", l));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_01) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %+010d - da", d),
                   sprintf(buffer_orig, "Yes, %+010d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_02) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-+10d - da", d),
                   sprintf(buffer_orig, "Yes, %-+10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_03) {
  char buffer[100];
  char buffer_orig[100];
  double d = 456.6;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, % 010f - da", d),
                   sprintf(buffer_orig, "Yes, % 010f - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_04) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#010x - da", d),
                   sprintf(buffer_orig, "Yes, %#010x - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_05) {
  char buffer[100];
  char buffer_orig[100];
  int d = 456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#-10x - da", d),
                   sprintf(buffer_orig, "Yes, %#-10x - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_06) {
  char buffer[100];
  char buffer_orig[100];
  int d = 0;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %#10.x - da", d),
                   sprintf(buffer_orig, "Yes, %#10.x - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_07) {
  char buffer[100];
  char buffer_orig[100];
  int d = 0;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %10.d - da", d),
                   sprintf(buffer_orig, "Yes, %10.d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_08) {
  char buffer[100];
  char buffer_orig[100];
  int d = -123456;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %5.10d - da", d),
                   sprintf(buffer_orig, "Yes, %5.10d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_09) {
  char buffer[100];
  char buffer_orig[100];
  int d = 0;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %5d - da", d),
                   sprintf(buffer_orig, "Yes, %5d - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_10) {
  char buffer[100];
  char buffer_orig[100];
  int d = 1234567;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-#5.10x - da", d),
                   sprintf(buffer_orig, "Yes, %-#5.10x - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

START_TEST(test_sprintf_combination_flags_11) {
  char buffer[100];
  char buffer_orig[100];
  int d = 0;
  ck_assert_int_eq(s21_sprintf(buffer, "Yes, %-10o - da", d),
                   sprintf(buffer_orig, "Yes, %-10o - da", d));
  ck_assert_str_eq(buffer, buffer_orig);
}
END_TEST

Suite *suite(void) {
  Suite *s = suite_create("s21_string_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_trim);
  tcase_add_test(tc_core, test_s21_insert);

  tcase_add_test(tc_core, test_sprintf_c);
  tcase_add_test(tc_core, test_sprintf_d);
  tcase_add_test(tc_core, test_sprintf_f);
  tcase_add_test(tc_core, test_sprintf_s);
  tcase_add_test(tc_core, test_sprintf_u);
  tcase_add_test(tc_core, test_sprintf_percent);

  tcase_add_test(tc_core, test_sprintf_x);
  tcase_add_test(tc_core, test_sprintf_X);
  tcase_add_test(tc_core, test_sprintf_o);
  tcase_add_test(tc_core, test_sprintf_p);
  tcase_add_test(tc_core, test_sprintf_width);
  tcase_add_test(tc_core, test_sprintf_width_star);
  tcase_add_test(tc_core, test_sprintf_precision);
  tcase_add_test(tc_core, test_sprintf_precision_star);
  tcase_add_test(tc_core, test_sprintf_length_ld);
  tcase_add_test(tc_core, test_sprintf_length_hd);
  tcase_add_test(tc_core, test_sprintf_length_lu);
  tcase_add_test(tc_core, test_sprintf_length_hu);
  tcase_add_test(tc_core, test_sprintf_length_L);
  tcase_add_test(tc_core, test_sprintf_flag_plus);
  tcase_add_test(tc_core, test_sprintf_flag_minus);
  tcase_add_test(tc_core, test_sprintf_flag_space);
  tcase_add_test(tc_core, test_sprintf_flag_zero);
  tcase_add_test(tc_core, test_sprintf_flag_hash);

  tcase_add_test(tc_core, test_sprintf_negative_width);
  tcase_add_test(tc_core, test_sprintf_negative_precision);
  tcase_add_test(tc_core, test_sprintf_negative_length);

  tcase_add_test(tc_core, test_sprintf_combination_flags_01);
  tcase_add_test(tc_core, test_sprintf_combination_flags_02);
  tcase_add_test(tc_core, test_sprintf_combination_flags_03);
  tcase_add_test(tc_core, test_sprintf_combination_flags_04);
  tcase_add_test(tc_core, test_sprintf_combination_flags_05);
  tcase_add_test(tc_core, test_sprintf_combination_flags_06);
  tcase_add_test(tc_core, test_sprintf_combination_flags_07);
  tcase_add_test(tc_core, test_sprintf_combination_flags_08);
  tcase_add_test(tc_core, test_sprintf_combination_flags_09);
  tcase_add_test(tc_core, test_sprintf_combination_flags_10);
  tcase_add_test(tc_core, test_sprintf_combination_flags_11);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}