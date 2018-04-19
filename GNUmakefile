all: main
	./main
clean:
	rm -rfv main src/dbg.o src/execution_context.o src/job_dispatcher.o src/logathlon.o src/main.o
main: src/dbg.o src/execution_context.o src/job_dispatcher.o src/logathlon.o src/main.o
	g++ -o main src/dbg.o src/execution_context.o src/job_dispatcher.o src/logathlon.o src/main.o -lpthread
src/dbg.o: src/dbg.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/dbg.o src/dbg.cpp
src/execution_context.o: src/execution_context.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/execution_context.o src/execution_context.cpp
src/job_dispatcher.o: src/job_dispatcher.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/job_dispatcher.o src/job_dispatcher.cpp
src/logathlon.o: src/logathlon.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/logathlon.o src/logathlon.cpp
src/main.o: src/main.cpp
	g++ -pedantic -std=c++1z -Wall -Wextra -O0 -g -Isrc -ftemplate-backtrace-limit=0 -c -o src/main.o src/main.cpp
.PHONY: clean all
