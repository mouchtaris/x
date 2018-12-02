#pragma once


///
/// tpf_construct
///
template <
	typename F
>
struct tpf_construct_tc;
template <
	typename F
>
using tpf_constructed_t = typename tpf_construct_tc<F>::result_t;

///
/// empty_tpf
///
template <
	typename F
>
struct empty_tpf : public std::false_type { };

///
/// tpf_construct facade
///
template <
	typename F,
	typename... CArgs
>
auto tpf_construct(CArgs&&... cargs)
-> tpf_constructed_t<F>
{
	return tpf_construct_tc<F>::call(std::forward<CArgs>(cargs)...);
}