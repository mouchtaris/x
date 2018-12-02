#pragma once
#include <tuple>
#include "Ghost.h"
#include "t.h"
namespace smaragd
{

	template <
		typename... Ts
	>
		struct make__tc
	{
		using result_type = std::tuple<Ts...>;


		template <
			template <typename...> typename K
		>
			struct _caller_args
		{
			using type = K<Ts...>;
		};


		template <
			typename... Args
		>
			auto _inject(Args&&... args)
		{
			return std::tuple<Args> {
				std::forward<Args>(args)...
			};
		}
	};

	template <
		typename T,
		typename... Ts
	>
		struct make__tc<std::tuple<Ghost<T>, Ts...>>
	{
		using _rest = make__tc<std::tuple<Ts...>>;

		using result_type = std::tuple<T, Ts...>;



		template <
			template <typename...> typename K
		>
			struct _caller_args
		{
			using type = typename _rest::template _caller_args<K>::type;
		};



		template <
			typename... Args
		>
			result_type _inject(Args&&... args)
		{
			return _rest::_inject(
				Ghost<T> {},
				std::forward<Args>(args)...
			);
		}



		template <
			typename... Args
		>
			struct _caller
		{
			result_type operator()(Args&&... args) const&
			{
				return _inject(
					std::forward<Args>(args)...
				);
			}
		};

		constexpr static auto call =
			typename _caller_args<_caller>::type{};
	};

	template <
		typename T
	>
		constexpr auto make = make__tc<T>::call;
}