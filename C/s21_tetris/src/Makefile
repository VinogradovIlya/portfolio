CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
CHECK_FLAGS = $(shell pkg-config --cflags check)
CHECK_LIBS = $(shell pkg-config --libs check)
LDFLAGS = -lncurses
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind.log --track-fds=yes

SRC_DIR = src
TETRIS_SRC_DIR = brick_game/tetris
GUI_SRC_DIR = gui/cli
TEST_DIR = tests/tetris

LIB_NAME = libs21_tetris.a
LIB_BACKEND_SRC = $(TETRIS_SRC_DIR)/s21_tetris_backend.c
LIB_BACKEND_OBJ = $(LIB_BACKEND_SRC:.c=.o)

TETRIS_SRC = $(wildcard $(TETRIS_SRC_DIR)/*.c)
TETRIS_SRCH = $(wildcard $(TETRIS_SRC_DIR)/*.h)
GUI_SRC = $(wildcard $(GUI_SRC_DIR)/*.c)
GUI_SRCH = $(wildcard $(GUI_SRC_DIR)/*.h)
MAIN_SRC = main.c
MAIN_SRCH = s21_tetris_common.h
SRCS = $(TETRIS_SRC) $(GUI_SRC) $(MAIN_SRC)
SRCSH = $(TETRIS_SRCH) $(GUI_SRCH) $(MAIN_SRCH)

TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
GUI_OBJ = $(GUI_SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)
OBJS = $(TETRIS_OBJ) $(GUI_OBJ) $(MAIN_OBJ)

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = s21_tetris
TEST_TARGET = test_tetris

DIST_DIR = s21_tetris_v1.0
HTML_COV_DIR = coverage

.PHONY: all install uninstall clean dvi dist test gcov_report rebuild

all: clean install

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(TETRIS_OBJ): $(TETRIS_SRC_DIR)/%.o: $(TETRIS_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GUI_OBJ): $(GUI_SRC_DIR)/%.o: $(GUI_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_BACKEND_OBJ)
	ar rcs $(LIB_NAME) $(LIB_BACKEND_OBJ)
	ranlib $(LIB_NAME)

install: uninstall $(TARGET) $(LIB_NAME)
	mkdir -p game/lib
	mv $(TARGET) game/
	mv $(LIB_NAME) game/lib/
	@echo "Installation successful to game"

uninstall: clean
	rm -rf game
	@echo "Uninstallation successful"

clean:
	rm -f $(OBJS) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) $(LIB_NAME) $(LIB_BACKEND_OBJ)
	rm -f $(TETRIS_SRC_DIR)/*.gcda $(TETRIS_SRC_DIR)/*.gcno
	rm -f *.gcda *.gcno *.info valgrind.log
	rm -rf $(HTML_COV_DIR) $(DIST_DIR) doc coverage.txt $(DIST_DIR).tar.gz record.txt
	@echo "Clean successful"

dvi:
	@echo "Creating Doxygen configuration file..."
	@mkdir -p doc
	@echo "PROJECT_NAME           = \"Tetris BrickGame\"" > doc/Doxyfile
	@echo "PROJECT_BRIEF         = \"Tetris game implemented in C with ncurses library\"" >> doc/Doxyfile
	@echo "OUTPUT_DIRECTORY      = doc" >> doc/Doxyfile
	@echo "INPUT                 = ." >> doc/Doxyfile
	@echo "RECURSIVE             = YES" >> doc/Doxyfile
	@echo "EXTRACT_ALL           = YES" >> doc/Doxyfile
	@echo "EXTRACT_PRIVATE       = YES" >> doc/Doxyfile
	@echo "EXTRACT_STATIC        = YES" >> doc/Doxyfile
	@echo "GENERATE_HTML         = YES" >> doc/Doxyfile
	@echo "GENERATE_LATEX        = NO" >> doc/Doxyfile
	@echo "HTML_OUTPUT           = html" >> doc/Doxyfile
	@echo "JAVADOC_AUTOBRIEF     = YES" >> doc/Doxyfile
	@echo "OPTIMIZE_OUTPUT_FOR_C = YES" >> doc/Doxyfile
	@echo "GENERATE_TREEVIEW     = YES" >> doc/Doxyfile
	@echo "HAVE_DOT             = NO" >> doc/Doxyfile
	@echo "SOURCE_BROWSER        = YES" >> doc/Doxyfile
	@echo "ALPHABETICAL_INDEX    = YES" >> doc/Doxyfile
	@echo "HTML_DYNAMIC_SECTIONS = YES" >> doc/Doxyfile
	@echo "SEARCHENGINE          = YES" >> doc/Doxyfile
	@echo "Generating documentation..."
	@doxygen doc/Doxyfile
	@echo "Documentation successfully generated in doc/html directory"
	@echo "To view, open doc/html/index.html in your browser"

dist: clean
	mkdir -p ../$(DIST_DIR)
	cp -r . ../$(DIST_DIR)
	cp -r Makefile ../$(DIST_DIR)
	tar -czvf ../$(DIST_DIR).tar.gz ../$(DIST_DIR)
	rm -rf ../$(DIST_DIR)
	mv ../$(DIST_DIR).tar.gz .
	@echo "Distribution package created: $(DIST_DIR).tar.gz"

test: $(TETRIS_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $(TETRIS_SRC) $(TEST_SRC) -o $(TEST_TARGET) $(CHECK_LIBS) $(LDFLAGS)
	./$(TEST_TARGET)

gcov_report:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS) $(TETRIS_SRC) $(TEST_SRC) -o $(TEST_TARGET) $(CHECK_LIBS) $(LDFLAGS)
	./$(TEST_TARGET)
	mkdir -p $(HTML_COV_DIR)
	gcovr --html --html-details -o $(HTML_COV_DIR)/index.html --exclude-throw-branches --exclude-unreachable-branches --exclude $(TEST_SRC)
	gcovr --txt -o coverage.txt --exclude-throw-branches --exclude-unreachable-branches
	@echo "Coverage report generated in $(HTML_COV_DIR)/index.html"
	@echo "Text coverage report:"
	# @cat coverage.txt
	open coverage/index.html

rebuild: clean test gcov_report

clang:
	clang-format -style=google -i $(SRCS) *.h $(TETRIS_SRC_DIR)/*.h $(GUI_SRC_DIR)/*.h $(TEST_SRC)
	@echo "Code style formatted"

valgrind: $(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TARGET) || true
	grep errors valgrind.log -n

adsan: test
	$(CC) $(CFLAGS_BASE) $(CFLAGS_ASAN) -fsanitize=address $(SRCS) -o $(TEST_TARGET) $(LDFLAGS)
	./$(TEST_TARGET)


cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRCS) $(SRCSH)
