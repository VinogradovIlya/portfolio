#ifndef GREP_H_
#define GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER 4096

typedef struct {
  int e;  // Шаблон
  int i;  // Игнорирует различия регистра
  int v;  // Инвертирует смысл поиска соответствий
  int c;  // Выводит только количество совпадающих строк
  int l;  // Выводит только совпадающие файлы.
  int n;  // Предваряет каждую строку вывода номером строки из файла ввода
  int h;  // Выводит совпадающие строки, не предваряя их именами файлов
  int s;  // Подавляет сообщения об ошибках о несуществующих или нечитаемых
          // файлах
  int f;  // Получает регулярные выражения из файла
  int o;  // Печатает только совпадающие (непустые) части совпавшей строки
} grep_options;

const char *short_opt = ":e:ivclnhsf:o";


void grep_parser(int argc, char *argv[]);
void switch_case(int opt, grep_options *flags, char *buffer, char *f_buffer,
                 char *argv[]);
void pattern_cr_e(char *argv[], char *buffer, char *pattern, int options);
void grep_reader(int argc, char *argv[], char *pattern, grep_options *flags);
void other_pattern_cr(int argc, char *argv[], char *pattern,
                      grep_options *flags, char *file_name_buffer);
void grep_s21(int argc, char *argv[], grep_options *flags, FILE *file_name,
              char *pattern, int current_file);
void grep_print(grep_options *flags, char *buffer, regex_t reg);

#endif
