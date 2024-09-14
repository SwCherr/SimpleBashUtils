CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -ggdb3

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep
	rm -rf *.log
	
clean:
	rm -rf *.log s21_grep