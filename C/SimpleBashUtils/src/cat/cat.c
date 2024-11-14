#include "cat.h"

#include "../common/base.h"

int main(int argc, char **argv) {
  int flags = 0;
  if (argc == 1) {
    read_and_print_input();
  } else {
    if (argv[1][0] == '-') {
      process_flags(argv[1], &flags);
    }
    for (int i = (flags ? 2 : 1); i < argc; ++i) {
      print_file(argv[i], flags);
    }
  }
  return 0;
}

void process_flags(const char *flag_str, int *flags) {
  while (*flag_str != '\0') {
    parse_flag(*flag_str, flags);
    flag_str++;
  }
}

void parse_flag(char flag, int *flags) {
  switch (flag) {
    case 'b':
      *flags |= FLAG_NUMBER_NONBLANK;
      break;
    case 'n':
      *flags |= FLAG_NUMBER;
      break;
    case 'e':
      *flags |= FLAG_SHOW_ENDS | FLAG_SHOW_NONPRINTING;
      break;
    case 's':
      *flags |= FLAG_SQUEEZE_BLANK;
      break;
    case 't':
      *flags |= FLAG_SHOW_TABS | FLAG_SHOW_NONPRINTING;
      break;
    case 'E':
      *flags |= FLAG_SHOW_ENDS;
      break;
    case 'T':
      *flags |= FLAG_SHOW_TABS;
      break;
    case 'v':
      *flags |= FLAG_SHOW_NONPRINTING;
      break;
  }
}

void read_and_print_input() {  // добавить работу с флагами
  char s;
  while (scanf("%c", &s) != EOF) {
    printf("%c", s);
  }
}

void print_line_number(int *line_number) { printf("%6d\t", (*line_number)++); }

void print_file(char *file, int flags) {
  FILE *f = fopen(file, "r");
  if (f != NULL) {
    int line_number = 1, c, last_char = 0, blank_lines_count = 0;
    int show_line_numbers = flags & FLAG_NUMBER;
    int number_non_blank = flags & FLAG_NUMBER_NONBLANK;
    int show_end_marker = flags & FLAG_SHOW_ENDS;
    int squeeze_blank = flags & FLAG_SQUEEZE_BLANK;
    int show_tabs = flags & FLAG_SHOW_TABS;

    if (show_line_numbers || number_non_blank) {
      print_line_number(&line_number);
    }
    while ((c = fgetc(f)) != EOF) {
      if (squeeze_blank && c == '\n' && last_char == '\n') {
        blank_lines_count++;
        if (blank_lines_count > 1) continue;
      } else {
        blank_lines_count = 0;
      }
      if (last_char == '\n' &&
          (show_line_numbers || (number_non_blank && c != '\n'))) {
        print_line_number(&line_number);
      }
      if (c == '\t' && show_tabs) {
        printf("^I");
      } else if (c == '\n' && show_end_marker) {
        putc('$', stdout);
        putc(c, stdout);
      } else {
        putc(c, stdout);
      }
      last_char = c;
    }
    fclose(f);
  } else {
    fprintf(stderr, "s21_cat: %s: %s\n", file, strerror(errno));
    exit(errno);
  }
}
