all: main
	./main
clean:
	rm -rfv main src/execution_context.o src/main.o
main: src/execution_context.o src/main.o
	g++ -o main src/execution_context.o src/main.o
src/execution_context.o: src/execution_context.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/execution_context.o src/execution_context.cpp
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
.PHONY: clean all
