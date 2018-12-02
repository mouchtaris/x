#pragma once

///
/// tpf_result_t<F, Args...>
///
template <
	typename F,
	typename... Args
>
using tpf_result_t = typename tpf<F, Args...>::result_t;