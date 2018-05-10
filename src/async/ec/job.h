#ifndef __ASYNC__EC__JOB_H__
#define __ASYNC__EC__JOB_H__
#include <functional>
#include "async/__common.h"

namespace async::ec
{
    TAGGED_VALUE(job, std::function<void()>);
}
#endif // __ASYNC__EC__JOB_H__
