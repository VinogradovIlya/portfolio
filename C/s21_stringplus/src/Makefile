CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
SOURCE=$(wildcard *.c) 
SOURCE:= $(filter-out tests.c, $(SOURCE))
OS=$(shell uname)
PKG_CONFIG=`pkg-config --cflags --libs check`

all: s21_string.a

s21_string.a:
	$(CC) $(FLAGS) -c $(SOURCE)
	ar -r s21_string.a *.o
	rm -f *.o

test:
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage -o main tests.c $(SOURCE) $(PKG_CONFIG)
	./main

gcov_report:
	@for file in $(SOURCE); do \
		echo "Processing $$file..."; \
		gcov -o . main-$$file; \
	done
	gcovr --html-details -o index.html --exclude tests.c
	rm -f *.gcda *.gcno *.a main coverage.info *.gcov *.o


clean:
	rm -f *.gcda *.gcno *.a main coverage.info *.gcov *.o log.txt
ifeq ($(OS), Darwin)
	rm -f *.css
	rm -rf *.html
else
	rm -rf coverage
	rm -f *.css
	rm -rf *.html
endif

rebuild: clean s21_string.a test gcov_report

rebuild_test: clean s21_string.a test

brew:
ifeq ($(OS), Darwin)
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install check
	brew install pkg-config
	brew install gcovr
else
	sudo apt update
	sudo apt install -y check pkg-config lcov gcovr
endif

clang:
	clang-format -i *.c
	clang-format -i *.h
	
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

valgrind: 
	valgrind --log-file=log.txt --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./main
	grep errors log.txt -n


	
	