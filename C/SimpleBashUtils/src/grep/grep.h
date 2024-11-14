#ifndef GREP_H
#define GREP_H

#define FLAG_PATTERN 1
#define FLAG_IGNORECASE 2
#define FLAG_INVERTED 4
#define FLAG_AMOUNT_MATCHING_LINES 8
#define FLAG_MATCHING_FILES 16

#define REG_ERROR 300
#define REG_COMPILE_ERROR 301
#define GREP_SYNTAX_ERROR 100

#include <regex.h>
#include <ctype.h>

void process_flags(const char *flag_str, int *flags);
void parse_flag(char flag_str, int *flags);
void foo(regex_t *regex);

#endif  // GREP_H
