#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void openfile(char *argv[]);
void cook_grep(FILE *, char expression[], char *file_name);
void func_oflag(char str[], regex_t regex);
void print_str(int beggin, int end, char string[]);
void cut_str(char new_str[], char str[], int index);
int compile_regex(regex_t *regex, char expression[]);

short eflag = 0;
short iflag = 0;
short vflag = 0;
short cflag = 0;
short lflag = 0;
short nflag = 0;
short hflag = 0;
short sflag = 0;
short fflag = 0;
short oflag = 0;
short mult_file_flag = 0;

#endif /*S21_GREP_H*/