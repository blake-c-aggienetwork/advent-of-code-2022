# compiler choice
CC = clang++

# compfiler flags
# -std=c++17 	+build with C++ 17
# -g					+adds debug info to executable file
# -Wall				+turns on compiler warnings
# -Wextra			+more warnings
# -Wpedantic	+helps display warnings
# 
CFLAGS = -std=c++17 -g -Wall -Wextra -Wpedantic

build: main

run: build
	./main.out

.PHONY: all
all: clean main

.PHONY: clean
clean:
	rm -f *.out *.o

# OBJECT FILES
main.o: main.cpp
	$(CC) main.cpp -c $(CFLAGS) -o main.o

utils.o: utils.cpp
	$(CC) utils.cpp -c $(CFLAGS) -o utils.o

# MAIN
main: main.o utils.o
	$(CC) main.o $(CFLAGS) -o main.out