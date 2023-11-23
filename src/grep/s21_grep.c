#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} Flag;

typedef struct {
  char *sample;
  char e_samples[10000];
} STORAGE;

void parsing_grep_flags(Flag *flags, STORAGE *storage, int argc, char *argv[],
                        int *flags_expression);
void case_e_sample(STORAGE *storage, char *optarg);
void case_f_sample(STORAGE *storage, char *optarg, Flag flags);
void save_samples_for_e_and_f(Flag flags, STORAGE *storage, char *argv[],
                              int optind, int *number);
void grep_without_l_c(FILE *file, regex_t *expression, Flag flags, char *argv[],
                      int argc, int *line_counter, int i);

int main(int argc, char *argv[]) {
  Flag flags = {0};
  STORAGE storage = {0};
  regex_t expression;
  int flags_expression = REG_EXTENDED;
  int number = 1;
  int line_counter = 0;
  bool there_is_line = false;
  parsing_grep_flags(&flags, &storage, argc, argv, &flags_expression);
  save_samples_for_e_and_f(flags, &storage, argv, optind, &number);
  for (int i = optind + number; i < argc; i++) {
    line_counter = 0;
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      if (!flags.s) {
        fprintf(stderr, ("%s: No such file or directory\n"), argv[optind + 1]);
      }
    } else if (regcomp(&expression, storage.sample, flags_expression) == 0) {
      grep_without_l_c(file, &expression, flags, argv, argc, &line_counter, i);
      // -l и -c
      there_is_line = false;
      if (line_counter > 0) {
        there_is_line = true;
      }
      if (flags.l && line_counter > 0 && flags.c && argc - optind < 3) {
        printf("%d\n%s\n", there_is_line, argv[i]);
      } else if (flags.c && flags.l) {
        if (there_is_line == false) {
          printf("%d\n", line_counter);
          continue;
        } else {
          printf("%s:%d\n", argv[i], there_is_line);
        }
        printf("%s\n", argv[i]);
      } else if (flags.l && there_is_line) {
        printf("%s\n", argv[i]);
      } else if (flags.c) {
        if (argc - optind > 2) {
          printf("%s:%d\n", argv[i], line_counter);
        } else {
          printf("%d\n", line_counter);
        }
      }
      fclose(file);
      regfree(&expression);
    } else {
      if (!flags.s) fprintf(stderr, ("Error Compile"));
    }
  }
  return 0;
}

void parsing_grep_flags(Flag *flags, STORAGE *storage, int argc, char *argv[],
                        int *flags_expression) {
  int ch = 0;
  while ((ch = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (ch) {
      case 'e':
        case_e_sample(storage, optarg);
        flags->e = REG_EXTENDED;
        break;
      case 'i':
        flags->i = 1;
        *flags_expression = 3;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 'f':
        flags->f = 1;
        case_f_sample(storage, optarg, *flags);
        break;
      case 's':
        flags->s = 1;
        break;
      case 'o':
        flags->o = 1;
        break;
    }
  }
}

void case_e_sample(STORAGE *storage, char *optarg) {
  strcat(storage->e_samples, optarg);
  strcat(storage->e_samples, "|");
}

void case_f_sample(STORAGE *storage, char *optarg, Flag flags) {
  char *line_from_file = NULL;
  int length_line_frome_file = 0;
  int res = 0;
  size_t size_line = 0;
  FILE *file_flag_f;
  file_flag_f = fopen(optarg, "r");

  if (file_flag_f == NULL) {
    if (!flags.s) {
      fprintf(stderr, ("s21_grep: %s: No such file or directory\n"), optarg);
    }
  } else {
    while ((res = getline(&line_from_file, &size_line, file_flag_f)) != EOF) {
      length_line_frome_file = strlen(line_from_file);
      if (line_from_file[length_line_frome_file - 1] == '\n') {
        line_from_file[length_line_frome_file - 1] = '|';
      }
      strcat(storage->e_samples, line_from_file);
    }
    free(line_from_file);
  }
  fclose(file_flag_f);
}

void save_samples_for_e_and_f(Flag flags, STORAGE *storage, char *argv[],
                              int optind, int *number) {
  if (flags.e || flags.f) {
    int length_e_samples = strlen(storage->e_samples);
    if (flags.e) {
      storage->e_samples[length_e_samples - 1] = '\0';
    }
    *number = 0;
    storage->sample = storage->e_samples;
  } else {
    storage->sample = argv[optind];
  }
}

void grep_without_l_c(FILE *file, regex_t *expression, Flag flags, char *argv[],
                      int argc, int *line_counter, int i) {
  char *line_from_file = NULL;
  size_t size_line = 0;
  int line_number = 0;
  int res = 0;
  regmatch_t flag_o_match;
  int match = 0;
  int print_line = 0;
  int add = 0;
  int length_line_frome_file = 0;

  while ((res = getline(&line_from_file, &size_line, file)) != EOF) {
    line_number++;
    print_line = 0;
    match = regexec(expression, line_from_file, 0, NULL, 0);
    if ((!flags.v && !match) || (flags.v && match)) {
      print_line = 1;
      *line_counter = *line_counter + 1;
    }
    if (print_line && !flags.l && !flags.c) {
      if (argc - optind > 2 && !flags.h) {
        printf("%s:", argv[i]);
      }
      if (flags.n) {
        printf("%d:", line_number);
      }
      length_line_frome_file = strlen(line_from_file);
      if (!flags.o) {
        if (line_from_file[length_line_frome_file - 1] != '\n') {
          printf("%s\n", line_from_file);
        } else {
          printf("%s", line_from_file);
        }
      } else {
        add = 0;
        while (regexec(expression, line_from_file + add, 1, &flag_o_match, 0) ==
               0) {
          for (int i = flag_o_match.rm_so + add; i < flag_o_match.rm_eo + add;
               i++) {
            printf("%c", line_from_file[i]);
          }
          printf("\n");
          add = flag_o_match.rm_eo + add;
        }
      }
    }
  }
  line_number = 0;
  free(line_from_file);
}