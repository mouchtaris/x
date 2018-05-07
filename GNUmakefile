CXX       = g++
CXXFLAGS  = -pedantic                     \
            -std=c++1z                    \
            -Wall                         \
            -Wextra                       \
            -O0                           \
            -g                            \
            -Isrc                         \
            -ftemplate-backtrace-limit=0
LDFLAGS   = -lpthread

all: main
run: all
	./main
clean:
	find src -iname '*.o' -print0 | xargs -0 rm -rvf
.PHONY: all run clean

main: \
              src/async/__common.h.o \


src/record.h.o: \
  src/record.h \
  src/tagged_value.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/record.h.o src/record.h

src/async/lockable.h.o: \
  src/async/lockable.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/lockable.h.o src/async/lockable.h

src/async/signal.h.o: \
  src/async/signal.h \
  src/async/lockable.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/signal.h.o src/async/signal.h

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/__common.h.o src/async/__common.h

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/__common.h.o src/async/__common.h

src/async/ec/job.h.o: \
  src/async/ec/job.h \
  src/async/__common.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/ec/job.h.o src/async/ec/job.h

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/__common.h.o src/async/__common.h

src/async/channel.h.o: \
  src/async/channel.h \
  src/async/lockable.h \ 
  src/async/signal.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/channel.h.o src/async/channel.h

src/async/ec/task.h.o: \
  src/async/ec/task.h \
  src/async/__common.h \ 
  src/async/ec/job.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/ec/task.h.o src/async/ec/task.h

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/__common.h.o src/async/__common.h

src/async/ec/task_channel.h.o: \
  src/async/ec/task_channel.h \
  src/async/__common.h \ 
  src/async/channel.h \ 
  src/async/ec/task.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/ec/task_channel.h.o src/async/ec/task_channel.h

src/async/__common.h.o: \
  src/async/__common.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/__common.h.o src/async/__common.h

src/async/ec/threadpool/worker.h.o: \
  src/async/ec/threadpool/worker.h \
  src/async/__common.h \ 
  src/async/ec/task_channel.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/ec/threadpool/worker.h.o src/async/ec/threadpool/worker.h

src/make_array.h.o: \
  src/make_array.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/make_array.h.o src/make_array.h

src/async/lockable.h.o: \
  src/async/lockable.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/lockable.h.o src/async/lockable.h

src/async/ec/threadpool.h.o: \
  src/async/ec/threadpool.h \
  src/async/__common.h \ 
  src/async/ec/threadpool/worker.h \ 
  src/make_array.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/ec/threadpool.h.o src/async/ec/threadpool.h

src/record.h.o: \
  src/record.h \
  src/tagged_value.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/record.h.o src/record.h

src/record.h.o: \
  src/record.h \
  src/tagged_value.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/record.h.o src/record.h

src/tagged_value.h.o: \
  src/tagged_value.h \
  src/tagname.h \ 
  src/tagged_value/fwd.h \ 
  src/tagged_value/write.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagged_value.h.o src/tagged_value.h

src/printf.h.o: \
  src/printf.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/printf.h.o src/printf.h

src/tagged_value/fwd.h.o: \
  src/tagged_value/fwd.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagged_value/fwd.h.o src/tagged_value/fwd.h

src/tagname.h.o: \
  src/tagname.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagname.h.o src/tagname.h

src/tagged_value/fwd.h.o: \
  src/tagged_value/fwd.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagged_value/fwd.h.o src/tagged_value/fwd.h

src/tagged_value/write.h.o: \
  src/tagged_value/write.h \
  src/tagged_value/fwd.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagged_value/write.h.o src/tagged_value/write.h

src/tagname.h.o: \
  src/tagname.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagname.h.o src/tagname.h

src/tagged_value.h.o: \
  src/tagged_value.h \
  src/tagname.h \ 
  src/tagged_value/fwd.h \ 
  src/tagged_value/write.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagged_value.h.o src/tagged_value.h

src/async/channel.h.o: \
  src/async/channel.h \
  src/async/lockable.h \ 
  src/async/signal.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/channel.h.o src/async/channel.h

src/async/signal.hpp.o: \
  src/async/signal.hpp \
  src/async/signal.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/signal.hpp.o src/async/signal.hpp

src/async/signal.h.o: \
  src/async/signal.h \
  src/async/lockable.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/signal.h.o src/async/signal.h

src/write::tuple.h.o: \
  src/write::tuple.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/write::tuple.h.o src/write::tuple.h

src/type.h.o: \
  src/type.h \
  src/tagname.h \ 
  src/tagged_value.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/type.h.o src/type.h

src/printf.h.o: \
  src/printf.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/printf.h.o src/printf.h

src/s.h.o: \
  src/s.h \
  src/printf.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/s.h.o src/s.h

src/model.h.o: \
  src/model.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/model.h.o src/model.h

src/copy.h.o: \
  src/copy.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/copy.h.o src/copy.h

src/json.h.o: \
  src/json.h \
  src/record.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/json.h.o src/json.h

src/async.h.o: \
  src/async.h \
  src/async/ec/threadpool.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async.h.o src/async.h

src/async/channel.hpp.o: \
  src/async/channel.hpp \
  src/async/channel.h \ 
  src/async/signal.hpp \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/async/channel.hpp.o src/async/channel.hpp

src/make_array.h.o: \
  src/make_array.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/make_array.h.o src/make_array.h

src/exp/sql.h.o: \
  src/exp/sql.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/exp/sql.h.o src/exp/sql.h

src/s.h.o: \
  src/s.h \
  src/printf.h \ 
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/s.h.o src/s.h

src/tagname.h.o: \
  src/tagname.h \
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -o src/tagname.h.o src/tagname.h

