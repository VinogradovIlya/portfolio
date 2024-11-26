#include "cat.h"

#include "../common/base.h"

int main(int argc, char **argv) {
  int flags = 0, start_read = 0;
  for (int i = 1; i < argc && start_read == 0; i++) {
    if (argv[i][0] == '-') {
      process_flags(argc, argv, &flags);
    } else {
      start_read = i;
    }
  }
  if (start_read == 0) {
    print_file(NULL, flags);
  } else {
    for (int i = start_read; i < argc; i++) {
      print_file(argv[i], flags);
    }
  }
  return 0;
}

void process_flags(int argc, char **argv, int *flags) {
  int opt;
  while ((opt = getopt_long(argc, argv, "bneEstv", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
      case 'n':
      case 'e':
      case 's':
      case 't':
      case 'v':
        parse_flag((char)opt, flags);
        break;
      default:
        fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
    }
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

void print_line_number_if_needed(int *line_number, int flags, int c) {
  int show_line_numbers = flags & FLAG_NUMBER;
  int number_non_blank = flags & FLAG_NUMBER_NONBLANK;
  if (show_line_numbers || (number_non_blank && c != '\n')) {
    if (!number_non_blank || c != '\n') {
      print_line_number(line_number);
    }
  }
}

void print_line_number(int *line_number) { printf("%6d\t", (*line_number)++); }

void print_file(char *file, int flags) {
  FILE *f = (file == NULL) ? stdin : fopen(file, "r");
  if (f != NULL) {
    int line_number = 1, c, last_char = 0, blank_lines_count = 0,
        is_first_line = 1;
    int show_line_numbers = flags & FLAG_NUMBER;
    int number_non_blank = flags & FLAG_NUMBER_NONBLANK;
    int show_end_marker = flags & FLAG_SHOW_ENDS;
    int squeeze_blank = flags & FLAG_SQUEEZE_BLANK;
    int show_tabs = flags & FLAG_SHOW_TABS;
    int show_nonprinting = flags & FLAG_SHOW_NONPRINTING;
    while ((c = fgetc(f)) != EOF) {
      if (squeeze_blank && c == '\n' && last_char == '\n') {
        blank_lines_count++;
        if (blank_lines_count > 1) continue;
      } else {
        blank_lines_count = 0;
      }
      if (is_first_line ||
          (last_char == '\n' &&
           (show_line_numbers || (number_non_blank && c != '\n')))) {
        print_line_number_if_needed(&line_number, flags, c);
        is_first_line = 0;
      }
      if (c < 32 && c != '\n' && c != '\t' && show_nonprinting) {
        printf("^%c", c + 64);
      } else if (c == 127 && show_nonprinting) {
        printf("^?");
      } else if (c == '\t' && show_tabs) {
        printf("^I");
      } else if (c == '\n') {
        if (show_end_marker) {
          fputc('$', stdout);
        }
        putc(c, stdout);
      } else {
        putc(c, stdout);
      }
      last_char = c;
    }
    if (file != NULL) {
      fclose(f);
    }
  } else if (file != NULL) {
    fprintf(stderr, "s21_cat: %s: %s\n", file, strerror(errno));
  }
}