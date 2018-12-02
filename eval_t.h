#pragma once

template <
	typename Expr
>
struct eval_impl;

template <
	typename Expr
>
using eval_t = typename eval_impl<Expr>::result_t;



template <
	template <typename...> typename T,
	typename... Args
>
struct apply_if_applicable_impl;
template <
	template <typename...> typename T,
	typename Arg,
	typename... Args
>
struct apply_if_applicable_impl<T, Arg, Args...>
{

};



template <
	typename F,
	typename List
>
struct select_impl; // = apply_if_applicable<...> {
	using head_t = 
};