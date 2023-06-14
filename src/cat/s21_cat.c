#include "s21_cat.h"

int main(int args, char *argv[]) {
  FILE *fp = NULL;
  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    const char *short_options = "benstvET";
    const struct option long_options[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {NULL, 0, NULL, 0}};

    int option;
    while ((option = getopt_long(args, argv, short_options, long_options,
                                NULL)) != -1) {
      if (option == 'b')
        bflag = nflag = 1;
      else if (option == 'e')
        eflag = vflag = 1;
      else if (option == 'n')
        nflag = 1;
      else if (option == 's')
        sflag = 1;
      else if (option == 't')
        tflag = vflag = 1;
      else if (option == 'v')
        vflag = 1;
      else if (option == 'E')
        eflag = 1;
      else if (option == 'T')
        tflag = 1;
      else {
        usage();
      }
    }
  }

  argv += optind;
  if (bflag || eflag || nflag || sflag || tflag || vflag)
    scanfiles(argv, 1);
  else
    scanfiles(argv, 0);
  fclose(fp);
  return 0;
}

void usage() {
    fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
    exit(1);
}

void scanfiles(char *argv[], int is_flag) {
  FILE *file_name = NULL;
  char *path;
  int i = 0;

  while ((path = argv[i]) != NULL || i == 0) {
    if (path == NULL || strcmp(path, "-") == 0) {
      file_name = stdin;
    } else
      file_name = fopen(path, "r");

    if (file_name) {
      if (!is_flag) {
        char ch;
        while ((ch = getc(file_name)) != EOF) {
          printf("%c", ch);
        }
      } else if (is_flag) {
        if (file_name == stdin)
          cook_cat(stdin);
        else {
          cook_cat(file_name);
        }
      }
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      exit(1);
    }

    ++i;
    if (file_name != stdin) fclose(file_name);
    if (path == NULL) break;
  }
}

void cook_cat(FILE *fp) {
  int ch, gobble, line, prev;
  int flag_continue = 0;

  line = gobble = 0;

  for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
    if (prev == '\n') {
      if (sflag) {
        if (ch == '\n') {
          if (gobble) flag_continue = 1;
          gobble = 1;
        } else
          gobble = 0;
      }

      if (!flag_continue) {
        if (nflag && (!bflag || ch != '\n')) {
          printf("%6d\t", ++line);
        }
      }
    }

    if (!flag_continue) {
      if (ch == '\n') {
        if (eflag) putchar('$');
      } else if (ch == '\t') {
        if (tflag) {
          putchar('^');
          putchar('I');
          flag_continue = 1;
        }
      } else if (vflag) {
        if (!isascii(ch) && !isprint(ch)) {
          putchar('M');
          putchar('-');
          ch = toascii(ch);
        }
        if (iscntrl(ch)) {
          putchar('^');
          putchar(ch == '\177' ? '?' : ch | 0100);
          flag_continue = 1;
        }
      }
      if (!flag_continue) putchar(ch);
    }
    flag_continue = 0;
  }
}