CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
SOURCE=$(wildcard *.c)
# SOURCE=s21_is_less.c s21_is_greater.c s21_is_equal.c s21_is_less_or_equal.c s21_is_greater_or_equal.c s21_is_not_equal.c tests.c helpers.c
SOURCE:= $(filter-out tests.c, $(SOURCE))
PKG_CONFIG=`pkg-config --cflags --libs check`
OS=$(shell uname)

all: s21_decimal.a

s21_decimal.a:
	$(CC) $(FLAGS) -c $(SOURCE)
	ar -r s21_decimal.a *.o
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
	rm -f *.gcda *.gcno *.a main coverage.info *.gcov *.o log.txt a.out
	rm -rf coverage
	rm -f *.css
	rm -rf *.html

rebuild: clean s21_decimal.a test gcov_report

rebuild_test: clean s21_decimal.a test

brew:
ifeq ($(OS), Darwin)
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install check
	brew install pkg-config
	brew install gcovr
else
	sudo apt update && sudo apt upgrade -y
	sudo apt install -y check pkg-config lcov gcovr
	# подкачать cppcheck, valgrind
endif

clang:
	clang-format -i *.c
	clang-format -i *.h
	
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

valgrind: 
	valgrind --log-file=log.txt --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./main
	grep errors log.txt -n

