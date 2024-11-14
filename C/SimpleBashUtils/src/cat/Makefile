CC = gcc
FLAGS = -Wall -Werror -Wextra
SOURCE = cat.c


s21_cat:
	$(CC) $(FLAGS) -o s21_cat $(SOURCE)

clear:
	rm s21_*

all: s21_cat

rebuild: clear all

clang:
	clang-format -i *.c *.h
