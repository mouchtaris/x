#pragma once

#include <utility>

#include "range.h"

#include "equal.h"
#include "next.h"

template <typename T, typename C>
void range(const T from, const T to, const C callback)
{
    callback(from);
    if (equal(from, to))
        return;
    auto&& n = next(from);
    if (n.has_value())
        range(n.value(), std::move(to), std::move(callback));
}
