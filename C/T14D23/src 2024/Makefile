#made by willames

CC=gcc
FLAGS=-Wall -Werror -Wextra
TARGET1=Quest_1
SOURCE=state_sort.c

all: $(TARGET1)

Quest_1:
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
	clang-format -i *.c
	git add $(SOURCE) Makefile
	git commit -m 'done $(SOURCE)'
	git push origin develop

init:
	cp ../materials/linters/.clang-format .
	git checkout -b develop