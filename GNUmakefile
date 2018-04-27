all: main
	./main
clean:
	rm -rfv main src/main.o
main: src/main.o
	g++ -o main src/main.o -lpthread
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
.PHONY: clean all
