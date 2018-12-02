#pragma once
#include "tpf.h"


///
/// tpf: compose<F, G>
///
template <
	typename F,
	typename G
>
struct compose;

template <
	typename F,
	typename G,
	typename... Args
>
struct tpf<compose<F, G>, Args...>
{
	using result_t = tpf_result_t<G, tpf_result_t<F, Args...>>;
};
