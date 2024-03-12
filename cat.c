#include "cat.h"

int main(int argc, char *argv[]) {
  struct for_flags flags[6] = {INIT_FLAGS};
  if (flag_parser(argc, argv, flags) == 0) {
    while (optind < argc) {
      open_and_print(argv, flags);
      optind++;
    }
  }
  return 0;
}

int flag_parser(char argc, char *argv[], struct for_flags *flags) {
  int your_flag = 0;
  int check = 0;
  static struct option words[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((your_flag = getopt_long(argc, argv, "+bEnsTvet?", words, NULL)) !=
         -1) {
    for (int i = 0; i < 6; i++) {
      if (flags[i].flag == your_flag) flags[i].state = 1;
    }
    if (your_flag == 'e') {
      flags[1].state = 1;
      flags[4].state = 1;
    }
    if (your_flag == 't') {
      flags[3].state = 1;
      flags[4].state = 1;
    }
    if (your_flag == '?') {
      printf("usage: ./s21_cat [-bEnsTvet] [file ...]\n");
      exit(1);
    }
  }
  return check;
}
// oprtind - параметр для getopt, по сути какой следfующий параметр читаем )
int open_and_print(char *argv[], struct for_flags *flags) {
  FILE *file;
  file = fopen(argv[optind], "r");
  if (file == NULL) {
    fprintf(stdout, "%s: %s: No such file or directory\n", argv[0],
            argv[optind]);
    return 1;
  }
  int string_counter = 1;
  int empty_string_counter = 0;
  int last = '\n';
  int now = 0;
  if (flags[0].state == 1) flags[2].state = 0;
  now = fgetc(file);
  while (now != EOF) {
    if (flags[5].state == 1 && now == '\n' && last == '\n') {
      empty_string_counter++;
      if (empty_string_counter > 1) {
        now = fgetc(file);
        continue;
      }
    } else {
      empty_string_counter = 0;
    }  // -s сжимает несколько смежных пустых строк
    if (last == '\n' &&
        ((flags[0].state == 1 && now != '\n') || flags[2].state == 1)) {
      printf("%6d\t", string_counter++);
    }  // -b нумерует только непустые строки and -n нумерует все выходные строки
    if (flags[1].state == 1 && now == '\n')
      printf("$");  // -E конец строки как $
    if (flags[3].state == 1 && now == '\t') {
      printf("^");
      now = 'I';
    }  // -T также отображает табы как ^I
    if (flags[4].state == 1 &&
        (((now < 32) && (now != '\n' && now != '\t')) || now == 127))
      printf("^");
    if (flags[4].state == 1 && (now > 127 && now < 160)) printf("M-^");
    if (flags[4].state == 1 && (now < 32 || (now > 126 && now < 160)) &&
        now != '\n' && now != '\t' && now != EOF) {
      now = now > 126 ? now - 128 + 64 : now + 64;
    }  // -v невидимые символы
    printf("%c", now);
    last = now;
    now = fgetc(file);
  }
  fclose(file);
  return 0;
}
