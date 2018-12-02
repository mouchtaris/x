#pragma once

#include "tpf_construct.h"

///
/// tpf_eval
///
template <
	typename F,
	typename... Args
>
struct tpf_eval_tc;

template <
	typename F,
	typename... Args
>
typename tpf_eval_tc<F, Args...>::result_t tpf_eval(
	tpf_constructed_t<F> f,
	Args&&... args
)
{
	return tpf_eval_tc<F, Args...>::call(f, std::forward<Args>(args)...);
}