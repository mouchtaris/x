#pragma once
#include <type_traits>
#include "../ghost.h"
#include "./type.h"
namespace smaragd::ast::node
{
	struct Tag;

	template <
		typename Type,
		typename Pimpl
	>
		using Node = std::tuple<
		Ghost<Tag>,
		Ghost<Type>,
		Pimpl
		>;

	template <
		typename T
	>
		struct tc;
	template <
		typename Type,
		typename Pimpl
	>
		struct tc<Node<Type, Pimpl>>
	{
		using type = Type;
		using pimpl_type = Pimpl;

		static Pimpl pimpl(Node<Type, Pimpl> node)
		{
			return std::get<2>(node);
		}
	};
	template <
		typename T
	>
		using node_type = typename tc<T>::type;
	template <
		typename T
	>
		using node_pimpl_t = typename tc<T>::pimpl_type;
	template <
		typename T
	>
		auto pimpl(T&& node)
	{
		return tc<T>::pimpl(std::forward<T>(node));
	}


	template <
		typename,
		typename = std::void_t<>
	>
		struct is_node__impl : public std::false_type {};
	template <
		typename T
	>
		struct is_node__impl<
		T,
		std::void_t<
		node_type<T>,
		node_pimpl_t<T>
		>
		> : public std::true_type {};
	template <
		typename T
	>
		using is_node_t = is_node__impl<T>;
	template <
		typename T
	>
		constexpr auto is_node = is_node_t<T>::value;


	template <
		typename Node
	>
		auto make(node_pimpl_t<Node> pimpl)
	{
		static_assert(is_node<Node>, "Not a node");

		return {
			{},
			{},
			std::move(pimpl)
		};
	}
}