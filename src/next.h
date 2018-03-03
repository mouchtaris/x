#pragma once
#include <optional>

template <typename T> struct Next;
template <typename T> std::optional<T> next(T n) { return Next<T> { }(std::move(n)); }
