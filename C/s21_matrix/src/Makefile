.PHONY: all clean test adsan gcov-report clang rebuild cppcheck valgrind download

CC=gcc
CFLAGS_BASE=-g -Wall -Werror -Wextra -std=c11
CFLAGS_ASAN=-fsanitize=address
# Флаги для тестов и покрытия
CFLAGS_TEST=$(CFLAGS_BASE)
CFLAGS_GCOV=$(CFLAGS_BASE) -fprofile-arcs -ftest-coverage
# Исполняемый файл тестов
TEST_EXECUTABLE=test_matrix
# Файлы библиотеки
LIB_SRC=$(wildcard s21_*.c)
LIB_OBJ=$(LIB_SRC:.c=.o)
# Файлы тестов
TEST_SRC=$(wildcard ../tests/*.c)
PKG_CONFIG=`pkg-config --cflags --libs check`
VALGRIND_FLAGS = --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind.log --track-fds=yes
COVERAGE_REPORT_HTML=coverage/index.html
COVERAGE_REPORT_LCOV=coverage.info

all: s21_matrix.a

s21_matrix.a: $(LIB_OBJ)
	ar -rcs s21_matrix.a $(LIB_OBJ)
	# rm -f $(LIB_OBJ)

$(LIB_OBJ): %.o: %.c s21_matrix.h s21_matrix_help.h
	$(CC) $(CFLAGS_BASE) -c $< -o $@

LIB_OBJ_GCOV=$(LIB_SRC:.c=.gcov.o)

$(LIB_OBJ_GCOV): %.gcov.o: %.c s21_matrix.h s21_matrix_help.h
	$(CC) $(CFLAGS_GCOV) -c $< -o $@

test: $(LIB_OBJ_GCOV) $(TEST_SRC)
	$(CC) $(CFLAGS_GCOV) -o $(TEST_EXECUTABLE) $(LIB_OBJ_GCOV) $(TEST_SRC) $(PKG_CONFIG)
	./$(TEST_EXECUTABLE)

gcov-report: test
	@mkdir -p coverage
	gcovr --html --html-details -o $(COVERAGE_REPORT_HTML) \
		--exclude ../tests/.* \
		--exclude-throw-branches --exclude-unreachable-branches \
		--print-summary --root .
	@echo "Coverage HTML report generated: $(COVERAGE_REPORT_HTML)"
	gcovr --lcov -o $(COVERAGE_REPORT_LCOV) \
		--exclude ../tests/.*  \
		--exclude-throw-branches --exclude-unreachable-branches \
		--root .
	@echo "Coverage LCOV report generated: $(COVERAGE_REPORT_LCOV)"

clean:
	rm -f *.gcda *.gcno *.a $(TEST_EXECUTABLE) *.info *.gcov *.o *.gcov.o log.txt a.out valgrind.log
	rm -rf coverage *.dSYM

adsan: $(LIB_SRC) $(TEST_SRC) s21_matrix.h s21_matrix_help.h
	$(CC) $(CFLAGS_BASE) $(CFLAGS_ASAN) $(LIB_SRC) $(TEST_SRC) $(PKG_CONFIG) -o $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clang:
	cp -n ../materials/linters/.clang-format .
	clang-format -n $(LIB_SRC) *.h $(TEST_SRC)
	rm -rf .clang-format

rebuild: clean all test gcov-report
	@echo "\033[1;32mRebuild, test, and coverage workflow complete. Report: $(COVERAGE_REPORT_HTML)\033[0m"

cppcheck:
	@echo "Running cppcheck..."
	cppcheck --enable=all --suppress=missingIncludeSystem $(LIB_SRC) ../include/*.h $(TEST_SRC)

valgrind: test
	valgrind $(VALGRIND_FLAGS) ./$(TEST_EXECUTABLE) || true
	grep errors valgrind.log -n

download:
	@echo "Please install necessary tools manually if needed:"
	@echo " - Ubuntu/Debian: sudo apt update && sudo apt install build-essential pkg-config check clang-format cppcheck valgrind gcovr"
	@echo " - macOS (Homebrew): brew install check clang-format cppcheck valgrind gcovr pkg-config"
