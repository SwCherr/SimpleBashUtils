#include "s21_grep.h"
int IS_FLAG = 0;

int main(int args, char *argv[]) {
  if (args < 2) {
    printf("usage: grep [-eivclnhsfo] template [file ...]\n");
  } else {
    const char *short_options = "eivclnhsfo";
    int option;

    while ((eflag != 1) &&
           ((option = getopt(args, argv, short_options)) != -1)) {
      if (option == 'e')
        eflag = 1;
      else if (option == 'i')
        iflag = 1;
      else if (option == 'v')
        vflag = 1;
      else if (option == 'c')
        cflag = 1;
      else if (option == 'l')
        lflag = 1;
      else if (option == 'n')
        nflag = 1;
      else if (option == 'h')
        hflag = 1;
      else if (option == 's')
        sflag = 1;
      else if (option == 'f')
        fflag = 1;
      else if (option == 'o')
        oflag = 1;

      else {
        fprintf(stderr, "usage: grep [-eivclnhsfo] template [file ...]\n");
        exit(1);
      }
    }

    argv += optind;
    if (optind > 0) IS_FLAG = 1;
    if ((args - (optind + 1)) > 1) mult_file_flag = 1;
    openfile(argv);
  }
  return 0;
}

void openfile(char *argv[]) {
  char expression[1024];
  strcpy(expression, argv[0]);
  argv += 1;

  char *file_name;
  int i = 0;
  while ((file_name = argv[i]) != NULL || i == 0) {
    FILE *fp = NULL;
    if (file_name == NULL) {
      if (!sflag)
        fprintf(stderr, "usage: grep [-eivclnhsfo] template [file ...]\n");
      fclose(fp);
    } else
      fp = fopen(file_name, "r");

    if (fp) {
      cook_grep(fp, expression, file_name);
      fclose(fp);
    } else if (!sflag)
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
    ++i;
  }
}

void cook_grep(FILE *fp, char expression[], char *file_name) {
  regex_t regex;
  int compile_res;
  compile_res = compile_regex(&regex, expression);

  if (compile_res != 0) {
    fprintf(stderr,
            "Invalid regular expression. Compilation error: error: %d.\n",
            compile_res);
    regfree(&regex);
    exit(1);
  } else {
    int flag_match = 0;
    int number_str = 1;
    char current_str[1024];
    int count_match_str = 0;

    while ((fgets(current_str, 1024, fp)) != NULL) {
      if (oflag)
        func_oflag(current_str, regex);
      else {
        int is_match = regexec(&regex, current_str, 0, NULL, 0);
        if (vflag) is_match = (!is_match);
        if (is_match == 0) {
          if (!cflag && !lflag) {
            if (mult_file_flag && !hflag) printf("%s:", file_name);
            if (nflag) printf("%d:", number_str);

            if (!oflag)
              printf("%s", current_str);
            else {
              for (size_t i = 1; i <= regex.re_nsub; i++)
                printf("%s", expression);
            }
          }
          count_match_str++;
          flag_match = 1;
        }
      }
      number_str++;
    }
    if (cflag) printf("%d", count_match_str);
    if (lflag && flag_match) printf("%s", file_name);
    if (flag_match && (!vflag || lflag || cflag)) printf("\n");
  }
  regfree(&regex);
}

int compile_regex(regex_t *regex, char expression[]) {
  int compile_res;
  if (iflag)
    compile_res = regcomp(regex, expression, REG_ICASE);
  else
    compile_res = regcomp(regex, expression, 0);
  return compile_res;
}

void func_oflag(char str[], regex_t regex) {
  size_t n_match = 2;
  regmatch_t pmatch[2];
  int is_match = regexec(&regex, str, n_match, pmatch, 0);

  if (is_match == 0) {
    int len_new_str = (int)strlen(str) - (int)pmatch[0].rm_eo;
    char new_str[len_new_str + 1];

    print_str((int)pmatch[0].rm_so, (int)pmatch[0].rm_eo, str);
    cut_str(new_str, str, (int)pmatch[0].rm_eo);
    func_oflag(new_str, regex);
  }
}

void print_str(int beggin, int end, char string[]) {
  for (int i = beggin; i < end; i++) printf("%c", string[i]);
  printf("\n");
}

void cut_str(char new_str[], char str[], int index) {
  int i = 0;
  while ((new_str[i] = str[index]) != '\0') {
    index++;
    i++;
  }
}