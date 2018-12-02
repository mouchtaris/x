#pragma once
#include "./node.h"
namespace smaragd::ast::parse
{

	struct ParserTag;

	template <
		typename... Addons
	>
		using Parser = std::tuple<
		Ghost<ParserTag>,
		std::tuple<
		Addons...
		>
		>;

	template <
		typename
	>
		struct parser_tc;
	template <
		typename... Addons
	>
		struct parser_tc<Parser<Addons...>>
	{

	};
}