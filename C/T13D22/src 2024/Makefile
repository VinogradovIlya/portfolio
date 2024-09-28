#made by willames

CC=gcc
FLAGS=-Wall -Werror -Wextra
TARGET1=cipher
SOURCE=cipher.c

all: cipher

cipher:
	$(CC) $(FLAGS) -o $(TARGET1) $(SOURCE)
	mv $(TARGET1) ../build

clean:
	rm -rf ../build/*

rebuild: clean all

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem .

leaks:
	leaks -atExit -- ./../build/$(TARGET1)

clang:
	clang-format -i *.c *.h
	git add $(SOURCE) Makefile
	git commit -m 'done $(SOURCE)'
	git push origin develop

init:
	cp ../materials/linters/.clang-format .
	git checkout -b develop