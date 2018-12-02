#pragma once
#include "tpf.h"


///
/// tpf: select<F, Args...>
///
struct select;
template <
	typename F
>
struct tpf<select, F>
{
	using result_t = std::tuple<>;

	static auto eval() { return std::tuple<>{}; }
};
template <
	typename F,
	typename Arg,
	typename... Args
>
struct tpf<select, F, Arg, Args...>
{
	using _is_defined = is_defined_at<F, Arg>;
	using _rest = tpf<select, F, Args...>;
	using _selected = std::conditional_t<
		std::conjunction_v<_is_defined>,
		std::tuple<tpf_result_t<F, Arg>>,
		std::tuple<>
	>;
	using result_t = decltype(
		std::tuple_cat(
			std::declval<_selected>(),
			std::declval<tpf_result_t<_rest>>()
		)
		);
};