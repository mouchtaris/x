all: main
	./main
clean:
	rm -rfv main src/command.o src/main.o
main: src/command.o src/main.o
	g++ -o main src/command.o src/main.o -lpthread
src/command.o: src/command.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/command.o src/command.cpp
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
.PHONY: clean all
