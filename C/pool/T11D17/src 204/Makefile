CC=gcc
CFLAGS=-Wall -Werror -Wextra
# SOURCES=dmanager_module.c
OBJECTS=$(SOURCES:.c=.o)
TARGET1=../build/Quest_1
TARGET2=../build/Quest_2

all: door_struct list_test

clang_start:
	cp ../materials/linters/.clang-format .

clang:
	clang-format -i *.c *.h
	git add .
	git commit -m '$(TARGET2) done'
	git push origin develop

clean:
	rm -rf *.o $(OBJECTS)
	rm ../build/Quest*

door_struct:
	$(CC) $(CFLAGS) -o $(TARGET1) dmanager_module.c

list_test:
	$(CC) $(CFLAGS) -o $(TARGET2) list_test.c list.c

rebuild: clean all

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem .

add:
	cd ..
	# git config --global user.email willames@student.21-school.ru
	# git config --global user.name willames
	git add .
	git commit -m 'task done'
	git push origin develop

# git:
# 	cd ..
# 	for entry in "*.out" ".idea" ".clang_format"; do
# 		if ! grep -qxF "$entry" .gitignore;  then
# 			echo "$entry" >> .gitignore
# 		fi
# 	done
