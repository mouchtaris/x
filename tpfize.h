#pragma once

#include "tpf.h"

///
/// tpf: tpfize<T, Args...>
///
template <
	template <typename...> typename T
>
struct tpfize;
template <
	template <typename...> typename T,
	typename... Args
>
struct tpf<tpfize<T>, Args...>
{
	using result_t = T<Args...>;
};
