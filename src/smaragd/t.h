#pragma once

namespace smaragd::t
{

	template <
		typename
	>
		struct evaluator_tc;



	template <
		template <typename...> typename K,
		typename... Bound
	>
		struct bind
	{
		template <
			typename... Args
		>
			using k = K<Bound..., Args...>;
	};

}