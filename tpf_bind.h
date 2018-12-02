#pragma once

#include <utility>
#include <tuple>
#include <functional>
#include <type_traits>

#include "tpf.h"
#include "tpf_construct.h"
#include "tpf_eval.h"
#include "tuples.h"

///
/// tpf: bind<F, Args...>
///
template <
	typename F,
	typename... Bound
>
struct bind;

template <
	typename F,
	typename... Bound,
	typename... Args
>
struct tpf<bind<F, Bound...>, Args...>
{
	using result_t = tpf_result_t<F, Bound..., Args...>;
};

template <
	typename F,
	typename... Bound
>
struct tpf_construct_tc<bind<F, Bound...>>
{
	using result_t = std::tuple<tpf_constructed_t<F>, std::tuple<Bound...>>;

	static auto call(tpf_constructed_t<F> f, Bound&&... args)
	{
		return result_t{ std::move(f), { std::forward<Bound>(args)... } };
	}
};

template <
	typename F,
	typename... Bound,
	typename... Args
>
struct tpf_eval_tc<bind<F, Bound...>, Args...>
{
	using _constructed = tpf_constructed_t<bind<F, Bound...>>;
	using _f_bind = std::tuple_element_t<0, _constructed>;
	using _bound = std::tuple_element_t<1, _constructed>;
	using result_t = _bound; //decltype(std::apply(std::declval<_f_bind>(), std::declval<_bound>()));

	static auto call(std::tuple<tpf_constructed_t<F>, std::tuple<Bound...>> cbind, Args&&... args)
	{
		//_f_bind f = std::get<0>(cbind);
		//_bound bound = std::get<1>(cbind);
		//auto all_args = std::tuple_cat(std::make_tuple(std::move(f)), std::move(bound), std::forward_as_tuple<Args...>(std::forward<Args>(args)...));
		//return std::apply(&tpf_eval<F, Bound..., Args...>, std::move(all_args));
		return result_t {};
	}
};