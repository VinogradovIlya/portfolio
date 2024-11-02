CC=gcc
CFLAGS=-Wall -Werror -Wextra
SOURCES=s21_string_test.c s21_string.c
OBJECTS=$(SOURCES:.c=.o)

strlen_tests:
	$(CC) $(CFLAGS) -Dq1 -o Quest_1 $(SOURCES)
	mv Quest_1 ../build

strcmp_tests:
	$(CC) $(CFLAGS) -Dq2 -o Quest_2 $(SOURCES)
	mv Quest_2 ../build

strcpy_tests:
	$(CC) $(CFLAGS) -Dq3 -o Quest_3 $(SOURCES)
	mv Quest_3 ../build

strcat_tests:
	$(CC) $(CFLAGS) -Dq4 -o Quest_4 $(SOURCES)
	cp Quest_4 ../build

strchr_tests:
	$(CC) $(CFLAGS) -Dq4 -o Quest_5 $(SOURCES)
	cp Quest_5 ../build

strstr_tests:
	$(CC) $(CFLAGS) -Dq4 -o Quest_6 $(SOURCES)
	cp Quest_6 ../build

strtok_tests:
	$(CC) $(CFLAGS) -Dq4 -o Quest_7 $(SOURCES)
	cp Quest_7 ../build

text_processor:
	$(CC) $(CFLAGS) -Dq4 -o Quest_7 $(SOURCES)
	cp Quest_7 ../build

clang:
	clang-format -i *.c *.h
	git add .
	git commit -m 'clang'
	git push origin develop

cleanQ:
	rm ../build/Quest*
	rm Quest*

clean:
	rm -rf *.o $(OBJECTS)

clean_all: clean cleanQ

add:
	git add .
	git commit -m 'task done'
	git push origin develop

git:
	echo "\n*.out\n*.o\n.clang-format" >> ../.gitignore