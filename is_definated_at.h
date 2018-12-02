#pragma once

#include "tpf.h"

#include <utility>

///
/// is_defined_at<F, Args...>
///

template <
	typename F,
	typename Indicator = std::void_t<>
>
struct _is_defined_impl : public std::false_type { };


template <
	typename F,
	typename... Args
>
struct _is_defined_impl<tpf<F, Args...>, std::void_t<typename tpf<F, Args...>::result_t>> : public std::true_type { };


template <
	typename F,
	typename... Args
>
using is_defined_at = _is_defined_impl<tpf<F, Args...>>;