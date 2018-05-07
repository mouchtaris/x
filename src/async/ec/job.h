#pragma once
#include <functional>
#include "async/__common.h"

namespace async::ec
{
    TAGGED_VALUE(job, std::function<void()>);
}
