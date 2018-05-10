CXX       = g++
CXXFLAGS  = -pedantic                     \
            -std=c++1z                    \
            -Wall                         \
            -Wextra                       \
            -Weffc++                      \
            -O0                           \
            -g                            \
            -Isrc                         \
            -ftemplate-backtrace-limit=0  \
            -fdiagnostics-show-option     \

LDFLAGS   = -lpthread

ifndef __mk_ready

MAKEFLAGS += --no-builtin-rules

.DEFAULT_GOAL := all

% :
	@$(MAKE) __mk_ready=1 $@

else

# ...

all: main
run: all
	./main
clean:
	find src -iname '*.o' -print0 | xargs -0 rm -rvf
.PHONY: all run clean

main: \
              src/async/__common.h.o \
               src/async/channel.h.o \
                src/async/ec/job.h.o \
               src/async/ec/task.h.o \
       src/async/ec/task_channel.h.o \
  src/async/ec/threadpool/worker.h.o \
         src/async/ec/threadpool.h.o \
              src/async/lockable.h.o \
                src/async/signal.h.o \
                       src/async.h.o \
                         src/bob.h.o \
                        src/copy.h.o \
                  src/exp/memsql.h.o \
              src/exp/memsqlrepo.h.o \
              src/exp/sql/is_col.h.o \
                 src/exp/sql/sdl.h.o \
                     src/exp/sql.h.o \
                        src/json.h.o \
                  src/make_array.h.o \
                      src/printf.h.o \
                      src/record.h.o \
                           src/s.h.o \
            src/tagged_value/fwd.h.o \
          src/tagged_value/write.h.o \
                src/tagged_value.h.o \
                     src/tagname.h.o \
                        src/talg.h.o \
           src/tuple\:\:for_each.h.o \
                        src/type.h.o \
              src/write\:\:tuple.h.o \
             src/async/channel.hpp.o \
              src/async/signal.hpp.o \
                      src/main.cpp.o \
                         src/s.cpp.o \
                   src/tagname.cpp.o \

	${CXX} -o main $^ ${LDFLAGS}

endif # __mk_ready

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/__common.h.o -xc++ src/async/__common.h

src/async/channel.h.o: \
  src/async/channel.h \
  src/async/lockable.h \
  src/async/signal.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/channel.h.o -xc++ src/async/channel.h

src/async/ec/job.h.o: \
  src/async/ec/job.h \
  src/async/__common.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/ec/job.h.o -xc++ src/async/ec/job.h

src/async/ec/task.h.o: \
  src/async/ec/task.h \
  src/async/__common.h \
  src/async/ec/job.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/ec/task.h.o -xc++ src/async/ec/task.h

src/async/ec/task_channel.h.o: \
  src/async/ec/task_channel.h \
  src/async/__common.h \
  src/async/channel.h \
  src/async/ec/task.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/ec/task_channel.h.o -xc++ src/async/ec/task_channel.h

src/async/ec/threadpool/worker.h.o: \
  src/async/ec/threadpool/worker.h \
  src/async/__common.h \
  src/async/ec/task_channel.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/ec/threadpool/worker.h.o -xc++ src/async/ec/threadpool/worker.h

src/async/ec/threadpool.h.o: \
  src/async/ec/threadpool.h \
  src/async/__common.h \
  src/async/ec/threadpool/worker.h \
  src/make_array.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/ec/threadpool.h.o -xc++ src/async/ec/threadpool.h

src/async/lockable.h.o: \
  src/async/lockable.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/lockable.h.o -xc++ src/async/lockable.h

src/async/signal.h.o: \
  src/async/signal.h \
  src/async/lockable.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/signal.h.o -xc++ src/async/signal.h

src/async.h.o: \
  src/async.h \
  src/async/ec/threadpool.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async.h.o -xc++ src/async.h

src/bob.h.o: \
  src/bob.h \
  src/exp/sql.h \
  src/exp/memsql.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/bob.h.o -xc++ src/bob.h

src/copy.h.o: \
  src/copy.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/copy.h.o -xc++ src/copy.h

src/exp/memsql.h.o: \
  src/exp/memsql.h \
  src/exp/sql.h \
  src/talg.h \
  src/record.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/exp/memsql.h.o -xc++ src/exp/memsql.h

src/exp/memsqlrepo.h.o: \
  src/exp/memsqlrepo.h \
  src/exp/memsql.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/exp/memsqlrepo.h.o -xc++ src/exp/memsqlrepo.h

src/exp/sql/is_col.h.o: \
  src/exp/sql/is_col.h \
  src/exp/sql/sdl.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/exp/sql/is_col.h.o -xc++ src/exp/sql/is_col.h

src/exp/sql/sdl.h.o: \
  src/exp/sql/sdl.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/exp/sql/sdl.h.o -xc++ src/exp/sql/sdl.h

src/exp/sql.h.o: \
  src/exp/sql.h \
  src/record.h \
  src/exp/sql/sdl.h \
  src/exp/sql/is_col.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/exp/sql.h.o -xc++ src/exp/sql.h

src/json.h.o: \
  src/json.h \
  src/record.h \
  src/tuple\:\:for_each.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/json.h.o -xc++ src/json.h

src/make_array.h.o: \
  src/make_array.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/make_array.h.o -xc++ src/make_array.h

src/printf.h.o: \
  src/printf.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/printf.h.o -xc++ src/printf.h

src/record.h.o: \
  src/record.h \
  src/tagged_value.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/record.h.o -xc++ src/record.h

src/s.h.o: \
  src/s.h \
  src/printf.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/s.h.o -xc++ src/s.h

src/tagged_value/fwd.h.o: \
  src/tagged_value/fwd.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tagged_value/fwd.h.o -xc++ src/tagged_value/fwd.h

src/tagged_value/write.h.o: \
  src/tagged_value/write.h \
  src/tagged_value/fwd.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tagged_value/write.h.o -xc++ src/tagged_value/write.h

src/tagged_value.h.o: \
  src/tagged_value.h \
  src/tagname.h \
  src/tagged_value/fwd.h \
  src/tagged_value/write.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tagged_value.h.o -xc++ src/tagged_value.h

src/tagname.h.o: \
  src/tagname.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tagname.h.o -xc++ src/tagname.h

src/talg.h.o: \
  src/talg.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/talg.h.o -xc++ src/talg.h

src/tuple\:\:for_each.h.o: \
  src/tuple\:\:for_each.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tuple\:\:for_each.h.o -xc++ src/tuple\:\:for_each.h

src/type.h.o: \
  src/type.h \
  src/tagname.h \
  src/tagged_value.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/type.h.o -xc++ src/type.h

src/write\:\:tuple.h.o: \
  src/write\:\:tuple.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/write\:\:tuple.h.o -xc++ src/write\:\:tuple.h

src/async/channel.hpp.o: \
  src/async/channel.hpp \
  src/async/channel.h \
  src/async/signal.hpp \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/channel.hpp.o -xc++ src/async/channel.hpp

src/async/signal.hpp.o: \
  src/async/signal.hpp \
  src/async/signal.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/async/signal.hpp.o -xc++ src/async/signal.hpp

src/main.cpp.o: \
  src/main.cpp \
  src/tagged_value/write.h \
  src/write\:\:tuple.h \
  src/type.h \
  src/printf.h \
  src/s.h \
  src/copy.h \
  src/json.h \
  src/async.h \
  src/async/channel.hpp \
  src/make_array.h \
  src/exp/sql.h \
  src/exp/memsql.h \
  src/talg.h \
  src/exp/memsqlrepo.h \
  src/bob.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/main.cpp.o -xc++ src/main.cpp

src/s.cpp.o: \
  src/s.cpp \
  src/s.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/s.cpp.o -xc++ src/s.cpp

src/tagname.cpp.o: \
  src/tagname.cpp \
  src/tagname.h \

	${CXX} ${CPPFLAGS} ${CXXFLAGS} -xc++ -pipe -c -o src/tagname.cpp.o -xc++ src/tagname.cpp

