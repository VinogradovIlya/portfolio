#ifndef CAT_H
#define CAT_H

#define FLAG_NUMBER_NONBLANK 1
#define FLAG_NUMBER 2
#define FLAG_SQUEEZE_BLANK 4
#define FLAG_SHOW_ENDS 8
#define FLAG_SHOW_TABS 16
#define FLAG_SHOW_NONPRINTING 32

#include <getopt.h>

static struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

void print_file(char *path, int flags);
void read_and_print_input();
void process_flags(const char *flag_str, int *flags);
void parse_flag(char flag, int *flags);
void print_line_number(int *line_number);

#endif  // CAT_H
