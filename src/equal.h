#pragma once
#include <utility>

template <typename T> struct Equal;
template <typename T> bool equal(T a, T b) { return Equal<T> { }(std::move(a), std::move(b)); }
