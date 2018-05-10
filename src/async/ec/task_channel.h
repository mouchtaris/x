#ifndef __ASYNC__EC__TASK_CHANNEL_H__
#define __ASYNC__EC__TASK_CHANNEL_H__
#include "async/__common.h"
#include "async/channel.h"
#include "async/ec/task.h"

namespace async::ec
{
    TAGGED_VALUE(task_channel, std::reference_wrapper<channel<task::rec>>);
}
#endif // __ASYNC__EC__TASK_CHANNEL_H__
