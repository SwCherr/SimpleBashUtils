CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -ggdb3

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat
	rm -rf *.log
	
clean:
	rm -rf *.log s21_cat