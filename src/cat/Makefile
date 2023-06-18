CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -ggdb3

all: s21_cat

s21_cat: s21_cat.o
	$(CC) s21_cat.o -o s21_cat

s21_cat.o:  s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c s21_cat.h

clean:
	rm -rf *.o *.so *.h.gch *.dSYM s21_cat