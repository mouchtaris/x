#pragma once
#include "async/__common.h"
#include "async/channel.h"
#include "async/ec/task.h"

namespace async::ec
{
    TAGGED_VALUE(task_channel, std::reference_wrapper<channel<task::rec>>);
}
