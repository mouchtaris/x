all: main
	./main
clean:
	rm -rfv main src/eval.o src/execution_context.o src/execution_context_spec.o src/main.o
main: src/eval.o src/execution_context.o src/execution_context_spec.o src/main.o
	g++ -o main src/eval.o src/execution_context.o src/execution_context_spec.o src/main.o -lpthread
src/eval.o: src/eval.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/eval.o src/eval.cpp
src/execution_context.o: src/execution_context.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/execution_context.o src/execution_context.cpp
src/execution_context_spec.o: src/execution_context_spec.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/execution_context_spec.o src/execution_context_spec.cpp
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
.PHONY: clean all
