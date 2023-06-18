CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -ggdb3

all: s21_grep

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

s21_grep.o:  s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c s21_grep.h

clean:
	rm -rf *.o *.so *.h.gch *.dSYM *.log s21_grep
