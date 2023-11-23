CC = gcc
CFLAG = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep:
	$(CC) $(CFLAG) s21_grep.c -o s21_grep

clean:
	rm -rf *.o s21_grep

rebuild: clean all

