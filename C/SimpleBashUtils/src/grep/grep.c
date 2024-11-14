#include "grep.h"

#include "../common/base.h"

int main(int argc, char *argv[]) {
  int flags = 0;
  if (argc >= 3) {
    if (argv[1][0] == '-') {
      process_flags(argv[1], &flags);
    }
    const char *pattern = argv[flags ? 2 : 1];
    regex_t regex;
    if ((regcomp(&regex, pattern, 0) != 0)) {
      fprintf(stderr, "Could not compile regex\n");
      exit(REG_ERROR);  // echo $?
    }
    foo(&regex);
    regfree(&regex);
  } else {
    fprintf(stderr, "Usage: grep [options] template [file_name]\n");
    exit(GREP_SYNTAX_ERROR);
  }

  return 0;
}

void process_flags(const char *flag_str, int *flags) {
  flag_str++;
  while (*flag_str) {
    parse_flag(*flag_str, flags);
    flag_str++;
  }
}

void parse_flag(char flag_str, int *flags) {
  switch (flag_str) {
    case 'e':
      *flags |= FLAG_PATTERN;
      break;
    case 'i':
      *flags |= FLAG_IGNORECASE;
      break;
    case 'v':
      *flags |= FLAG_INVERTED;
      break;
    case 'c':
      *flags |= FLAG_AMOUNT_MATCHING_LINES;
      break;
    case 'l':
      *flags |= FLAG_MATCHING_FILES;
      break;
    default:
      fprintf(stderr, "Unknown flag: %c\n", flag_str);
  }
}

void match(regex_t *regex) {
  const char *test_str = "example";
  int reti = regexec(regex, test_str, 0, NULL, 0);
  if (!reti) {
    printf("Match\n");
  } else if (reti == REG_NOMATCH) {
    printf("No match\n");
  } else {
    size_t length = regerror(reti, regex, NULL, 0);
    char *error_message = (char *)malloc(length);
    if (error_message != NULL) {
      regerror(reti, regex, error_message, length);
      fprintf(stderr, "Regex match failed: %s\n", error_message);
      free(error_message);
    } else {
      fprintf(stderr, "Memory allocation error\n");
    }
  }
}

void lower_match(const char *file, const char *pattern) {
  FILE *f = fopen(file, "r");
  int len = fread(pattern, 1, strlen(pattern), f);
  if (f != NULL) {
    while (fgetc(f) != EOF) {

    }
  } else {
    fprintf(stderr, "lower: %s: %s\n", file, strerror(errno));
    exit(errno);
  }


  return ;
}