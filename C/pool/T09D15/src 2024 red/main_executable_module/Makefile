CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
SOURCES=main_executable_module.c ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
OBJECTS=$(SOURCES:.c=.o)

all: main_executable_module.o data_io.o data_stat.o data_process.o decision.o
	$(CC) main_executable_module.o data_io.o data_stat.o data_process.o decision.o -o Quest_3
	mv Quest_3 ../../build

data_stat.a: data_stat.o
	ar rcs data_stat.a data_stat.o

build_with_static: data_stat.a data_stat.o main_executable_module.o data_io.o decision.o data_process.o
	$(CC) main_executable_module.o data_io.o data_stat.a data_process.o decision.o -o Quest_5
	mv Quest_5 ../../build

data_process.so: data_stat.o
	$(CC) $(CFLAGS) -fPIC ../data_module/data_process.c
	$(CC) -shared -o data_process.so *.o

build_with_dynamic: data_process.so main_executable_module.o data_io.o decision.o 
	$(CC) -o Quest_6 *.o data_process.so
	mv Quest_6 ../../build
	mv data_process.so ../../build

main_executable_module.o: main_executable_module.c
	$(CC) $(CFLAGS) main_executable_module.c

data_io.o: ../data_libs/data_io.c
	$(CC) $(CFLAGS) ../data_libs/data_io.c

data_stat.o: ../data_libs/data_stat.c
	$(CC) $(CFLAGS) ../data_libs/data_stat.c

data_process.o: ../data_module/data_process.c
	$(CC) $(CFLAGS) ../data_module/data_process.c

decision.o: ../yet_another_decision_module/decision.c
	$(CC) $(CFLAGS) ../yet_another_decision_module/decision.c

clean:
	rm -rf *.o $(OBJECTS)

rebuild: clean all
