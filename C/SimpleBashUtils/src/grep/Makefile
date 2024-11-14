CC = gcc
FLAGS = -Wall -Werror -Wextra
SOURCE = grep.c


s21_grep:
	$(CC) $(FLAGS) -o s21_grep $(SOURCE)

clear:
	rm s21_*

all: s21_grep

rebuild: clear all

clang:
	clang-format -i *.c *.h
