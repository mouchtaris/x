all: main
	./main
clean:
	rm -rfv main src/main.o src/tagname.o
main: src/main.o src/tagname.o
	g++ -o main src/main.o src/tagname.o -lpthread
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
src/tagname.o: src/tagname.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/tagname.o src/tagname.cpp
.PHONY: clean all
