#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INIT_FLAGS \
  {'b', 0}, {'E', 0}, {'n', 0}, {'T', 0}, {'v', 0}, { 's', 0 }
typedef int bool;
struct for_flags {
  char flag;
  bool state;
};
int flag_parser(char argc, char *argv[], struct for_flags *flags);
int open_and_print(char *argv[], struct for_flags *flags);
