all: main
	./main
clean:
	rm -rfv main main.o
main: main.o
	g++ -o main main.o
main.o:
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -Isrc -c -o main.o main.cpp
.PHONY: clean all
