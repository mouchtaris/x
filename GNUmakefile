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
                        src/copy.h.o \
                     src/exp/sql.h.o \
                        src/json.h.o \
                  src/make_array.h.o \
                       src/model.h.o \
                      src/printf.h.o \
                      src/record.h.o \
                           src/s.h.o \
            src/tagged_value/fwd.h.o \
          src/tagged_value/write.h.o \
                src/tagged_value.h.o \
                     src/tagname.h.o \
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

	cat src/async/__common.h | \
	  sed -r -e '1a# 1 "src/async/__common.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/__common.h.o -xc++ -

src/async/channel.h.o: \
  src/async/channel.h \
  src/async/lockable.h \
  src/async/signal.h \

	cat src/async/channel.h | \
	  sed -r -e '1a# 1 "src/async/channel.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/channel.h.o -xc++ -

src/async/ec/job.h.o: \
  src/async/ec/job.h \
  src/async/__common.h \

	cat src/async/ec/job.h | \
	  sed -r -e '1a# 1 "src/async/ec/job.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/ec/job.h.o -xc++ -

src/async/ec/task.h.o: \
  src/async/ec/task.h \
  src/async/__common.h \
  src/async/ec/job.h \

	cat src/async/ec/task.h | \
	  sed -r -e '1a# 1 "src/async/ec/task.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/ec/task.h.o -xc++ -

src/async/ec/task_channel.h.o: \
  src/async/ec/task_channel.h \
  src/async/__common.h \
  src/async/channel.h \
  src/async/ec/task.h \

	cat src/async/ec/task_channel.h | \
	  sed -r -e '1a# 1 "src/async/ec/task_channel.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/ec/task_channel.h.o -xc++ -

src/async/ec/threadpool/worker.h.o: \
  src/async/ec/threadpool/worker.h \
  src/async/__common.h \
  src/async/ec/task_channel.h \

	cat src/async/ec/threadpool/worker.h | \
	  sed -r -e '1a# 1 "src/async/ec/threadpool/worker.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/ec/threadpool/worker.h.o -xc++ -

src/async/ec/threadpool.h.o: \
  src/async/ec/threadpool.h \
  src/async/__common.h \
  src/async/ec/threadpool/worker.h \
  src/make_array.h \

	cat src/async/ec/threadpool.h | \
	  sed -r -e '1a# 1 "src/async/ec/threadpool.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/ec/threadpool.h.o -xc++ -

src/async/lockable.h.o: \
  src/async/lockable.h \

	cat src/async/lockable.h | \
	  sed -r -e '1a# 1 "src/async/lockable.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/lockable.h.o -xc++ -

src/async/signal.h.o: \
  src/async/signal.h \
  src/async/lockable.h \

	cat src/async/signal.h | \
	  sed -r -e '1a# 1 "src/async/signal.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/signal.h.o -xc++ -

src/async.h.o: \
  src/async.h \
  src/async/ec/threadpool.h \

	cat src/async.h | \
	  sed -r -e '1a# 1 "src/async.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async.h.o -xc++ -

src/copy.h.o: \
  src/copy.h \

	cat src/copy.h | \
	  sed -r -e '1a# 1 "src/copy.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/copy.h.o -xc++ -

src/exp/sql.h.o: \
  src/exp/sql.h \
  src/record.h \

	cat src/exp/sql.h | \
	  sed -r -e '1a# 1 "src/exp/sql.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/exp/sql.h.o -xc++ -

src/json.h.o: \
  src/json.h \
  src/record.h \

	cat src/json.h | \
	  sed -r -e '1a# 1 "src/json.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/json.h.o -xc++ -

src/make_array.h.o: \
  src/make_array.h \

	cat src/make_array.h | \
	  sed -r -e '1a# 1 "src/make_array.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/make_array.h.o -xc++ -

src/model.h.o: \
  src/model.h \
  src/record.h \

	cat src/model.h | \
	  sed -r -e '1a# 1 "src/model.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/model.h.o -xc++ -

src/printf.h.o: \
  src/printf.h \

	cat src/printf.h | \
	  sed -r -e '1a# 1 "src/printf.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/printf.h.o -xc++ -

src/record.h.o: \
  src/record.h \
  src/tagged_value.h \

	cat src/record.h | \
	  sed -r -e '1a# 1 "src/record.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/record.h.o -xc++ -

src/s.h.o: \
  src/s.h \
  src/printf.h \

	cat src/s.h | \
	  sed -r -e '1a# 1 "src/s.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/s.h.o -xc++ -

src/tagged_value/fwd.h.o: \
  src/tagged_value/fwd.h \

	cat src/tagged_value/fwd.h | \
	  sed -r -e '1a# 1 "src/tagged_value/fwd.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/tagged_value/fwd.h.o -xc++ -

src/tagged_value/write.h.o: \
  src/tagged_value/write.h \
  src/tagged_value/fwd.h \

	cat src/tagged_value/write.h | \
	  sed -r -e '1a# 1 "src/tagged_value/write.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/tagged_value/write.h.o -xc++ -

src/tagged_value.h.o: \
  src/tagged_value.h \
  src/tagname.h \
  src/tagged_value/fwd.h \
  src/tagged_value/write.h \

	cat src/tagged_value.h | \
	  sed -r -e '1a# 1 "src/tagged_value.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/tagged_value.h.o -xc++ -

src/tagname.h.o: \
  src/tagname.h \

	cat src/tagname.h | \
	  sed -r -e '1a# 1 "src/tagname.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/tagname.h.o -xc++ -

src/type.h.o: \
  src/type.h \
  src/tagname.h \
  src/tagged_value.h \

	cat src/type.h | \
	  sed -r -e '1a# 1 "src/type.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/type.h.o -xc++ -

src/write\:\:tuple.h.o: \
  src/write\:\:tuple.h \

	cat src/write\:\:tuple.h | \
	  sed -r -e '1a# 1 "src/write\:\:tuple.h"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/write\:\:tuple.h.o -xc++ -

src/async/channel.hpp.o: \
  src/async/channel.hpp \
  src/async/channel.h \
  src/async/signal.hpp \

	cat src/async/channel.hpp | \
	  sed -r -e '1a# 1 "src/async/channel.hpp"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/channel.hpp.o -xc++ -

src/async/signal.hpp.o: \
  src/async/signal.hpp \
  src/async/signal.h \

	cat src/async/signal.hpp | \
	  sed -r -e '1a# 1 "src/async/signal.hpp"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/async/signal.hpp.o -xc++ -

src/main.cpp.o: \
  src/main.cpp \
  src/write\:\:tuple.h \
  src/type.h \
  src/printf.h \
  src/s.h \
  src/model.h \
  src/copy.h \
  src/json.h \
  src/async.h \
  src/async/channel.hpp \
  src/make_array.h \
  src/exp/sql.h \

	cat src/main.cpp | \
	  sed -r -e '1a# 1 "src/main.cpp"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/main.cpp.o -xc++ -

src/s.cpp.o: \
  src/s.cpp \
  src/s.h \

	cat src/s.cpp | \
	  sed -r -e '1a# 1 "src/s.cpp"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/s.cpp.o -xc++ -

src/tagname.cpp.o: \
  src/tagname.cpp \
  src/tagname.h \

	cat src/tagname.cpp | \
	  sed -r -e '1a# 1 "src/tagname.cpp"' | \
	  sed -r -e '$$anamespace { static const auto __file_name = __FILE__\; }' | \
	  grep -v -E -e '^[[:space:]]*\#[[:space:]]*pragma[[:space:]]*once' | \
	  ${CXX} ${CPPFLAGS} ${CXXFLAGS} -c -pipe -o src/tagname.cpp.o -xc++ -

