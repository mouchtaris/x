#pragma once

#include <utility>

template <typename T> struct Constructor;
template <typename T, typename... Args> T construct(Args&&... args);
