all: s21_grep

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: s21_grep

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

s21_grep.o:  s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c s21_grep.h

clean:
	rm -rf *.o *.so *.h.gch s21_grep
