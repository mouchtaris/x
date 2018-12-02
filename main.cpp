#include <tuple>
#include <iostream>
#include <type_traits>
#include <string>
#include <utility>
#include <deque>
#include <memory>
#include <type_traits>

#include "tpf.h"
#include "is_definated_at.h"
#include "tpf_result_t.h"
#include "tpf_construct.h"
#include "tpf_eval.h"
#include "tpf_bind.h"
#include "tpf_select.h"
#include "tpfize.h"
#include "tuples.h"

#include "smaragd/ast/parse.h"
#include "smaragd/LoggingParsingAdapter.h"
#include "smaragd/make.h"

using Integer = smaragd::ast::node::Node<smaragd::ast::type::Integer, uint64_t>;

void test_sm()
{
	using namespace smaragd;
	using namespace ast;

	
	make__tc<std::tuple<Ghost<bool>, Ghost<node::Tag>, Ghost<type::Integer>, uint64_t>> a{};
	make__tc<std::tuple<Ghost<type::Integer>, uint64_t>> b{};

	b.call(67);
	//make<Integer>(65);
}










constexpr auto nl = '\n';
using isint = bind<tpfize<std::is_same>, int>;

template <> struct tpf_construct_tc<tpfize<std::is_same>> {
	using result_t = unit_t;
	using cargs_t = unit_t;
	static auto call() { return unit; }
};
template <> struct tpf_eval_tc<tpfize<std::is_same>> {
	using result_t = bool;
	template <
		typename A,
		typename B,
		typename = std::enable_if_t<std::is_same_v<A, B>, void>
	>
	static auto call(A&& a, B&& b)
	{
		return a == b;
	}
};

int main(int, char**)
{
	std::cout
		<< is_defined_at<select, int>::value << nl
		<< is_defined_at<isint, int>::value << nl
		<< std::endl;

	auto wat1 = tpf_construct<tpfize<std::is_same>>();
	auto wat = tpf_construct<isint>(std::move(wat1), 1);
	auto wot = tpf_eval<isint>(std::move(wat), 1);

	test_sm();

	std::string wait;
	std::getline(std::cin, wait);

	return 0;
}