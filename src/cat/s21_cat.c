#include <getopt.h>
#include <stdio.h>
typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flag;

void parsing_cat_flags(char ch, Flag *flags, char *short_options,
                       struct option long_options[], int argc, char *argv[]);
void nice_cat(int ch, FILE *file, Flag flags, int argc, char *argv[],
              int number, int string_eater);

int main(int argc, char *argv[]) {
  FILE *file;
  file = NULL;
  Flag flags = {0};
  char ch = 0;
  char *short_options = "+beEnstTv";
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};
  int number = 1;
  int string_eater = 0;
  parsing_cat_flags(ch, &flags, short_options, long_options, argc, argv);
  nice_cat(ch, file, flags, argc, argv, number, string_eater);
  return 0;
}

void parsing_cat_flags(char ch, Flag *flags, char *short_options,
                       struct option long_options[], int argc, char *argv[]) {
  while ((ch = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (ch) {
      case 'b':
        flags->b = 1;
        flags->n = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
    }
  }
}

void nice_cat(int ch, FILE *file, Flag flags, int argc, char *argv[],
              int number, int string_eater) {
  for (int i = optind; i < argc; i++) {
    file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, ("s21_cat: %s: No such file or directory:\n"), argv[i]);
    } else {
      for (char prev = '\n'; (ch = fgetc(file)) != EOF; prev = ch) {
        if (flags.s == 1) {
          if (prev == '\n' && ch == '\n') {
            if (string_eater == 1) {
              continue;
            }
            string_eater = 1;
          } else {
            string_eater = 0;
          }
        }
        if (flags.n == 1 && (!flags.b || ch != '\n') && prev == '\n') {
          printf("%6d\t", number);
          number = number + 1;
        }
        if (flags.e && ch == '\n') {
          printf("$");
        }
        if (flags.t && ch == '\t') {
          printf("^");
          ch = ch + 64;
        }
        if (flags.v == 1) {
          if ((ch <= 8 && ch >= 0) || (ch >= 11 && ch <= 31)) {
            printf("^");
            ch = ch + 64;
          } else if (ch == 127) {
            printf("^");
            ch = ch - 64;
          } else if (ch >= 128 && ch <= 159) {
            printf("M-^");
            ch = ch - 64;
          } else if (ch >= 160 && ch <= 255) {
            printf("M-");
            ch = ch - 128;
          }
        }
        printf("%c", ch);
      }
    }
    fclose(file);
    number = 1;
  }
}