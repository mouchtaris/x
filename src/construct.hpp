#pragma once

#include "construct.h"

template <
    typename T,
    typename... Args
>
T construct(Args&&... args)
{
    return Constructor<T>::create(std::forward<Args>(args)...);
}
