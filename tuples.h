#pragma once

#include <tuple>

template <
	size_t... I,
	typename T
>
auto _subtuple(T&& t, std::index_sequence<I...>)
{
	return std::make_tuple(std::get<I>(t)...);
}

template <
	size_t from,
	typename T
>
auto subtuple_from(T&& t)
{
	return _subtuple(std::forward<T>(t), std::make_index_sequence<std::tuple_size_v<T> - from>{});
}

using unit_t = std::tuple<>;
static constexpr unit_t unit = {};