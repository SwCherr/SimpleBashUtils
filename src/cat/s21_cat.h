#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage();
void scanfiles(char *argv[], int is_flag);
void cook_cat(FILE *);

int bflag = 0;
int eflag = 0;
int nflag = 0;
int sflag = 0;
int tflag = 0;
int vflag = 0;

#endif /*S21_CAT_H*/