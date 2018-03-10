all: main
	./main
clean:
	rm -rfv main src/main.o src/tokens.o
main: src/main.o src/tokens.o
	g++ -o main src/main.o src/tokens.o
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -c -o src/main.o src/main.cpp
src/tokens.o: src/tokens.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -c -o src/tokens.o src/tokens.cpp
.PHONY: clean all
