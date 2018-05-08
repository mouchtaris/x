#pragma once
#include <type_traits>
#include <tuple>

namespace talg
{

    template <
        typename _tuple1,
        typename _tuple2>
    using tuple_cat_t = decltype(
        std::tuple_cat(
            std::declval<_tuple1>(),
            std::declval<_tuple2>()
        )
    );

    template <typename tuple> struct tuple_elements;
    template <
        typename ...Ts>
    struct tuple_elements<std::tuple<Ts...>>
    {
        template <template <typename...> class F>
        using apply_t = F<Ts...>;
    };
    template <
        typename tuple,
        template <typename...> class F>
    using tuple_elements_t = typename tuple_elements<tuple>::template apply_t<F>;

    ///
    //////
    ////////////
    //////
    ///

    template <typename _pf>
    struct pf
    {
        template <typename ...Args> struct is_defined_at: public _pf::template is_defined_at<Args...> { };
        template <typename ...Args> struct apply: public _pf::template apply<Args...> { };
    };

    ///
    //////
    ////////////
    //////
    ///

    template <typename ...Args> struct tuple_list;
    template <
        typename _head,
        typename ..._tail>
    struct tuple_list<_head, _tail...>
    {
        template <template <typename...> class F>
        using apply_head_t = F<_head>;
        template <template <typename...> class F>
        using apply_tail_t = F<_tail...>;
    };

    template <typename ...Args>
    using head_t = typename tuple_list<Args...>::head;

    template <
        template <typename...> class F,
        typename ..._Args>
    using tail_t = typename tuple_list<_Args...>::template apply_tail_t<F>;

    ///
    //////
    ////////////
    //////
    ///

    template <
        bool condition,
        template <typename...> class IfTrue,
        template <typename...> class IfFalse
        >
    struct apply_if_else
    {
        template <typename...Args>
        using apply_t = IfFalse<Args...>;
    };

    template <
        template <typename...> class IfTrue,
        template <typename...> class IfFalse>
    struct apply_if_else<true, IfTrue, IfFalse>
    {
        template <typename...Args>
        using apply_t = IfTrue<Args...>;
    };

    template <
        bool condition,
        template <typename...> class IfTrue,
        template <typename...> class IfFalse,
        typename ...Args
        >
    using apply_if_else_t = typename
        apply_if_else<condition, IfTrue, IfFalse>::
        template apply_t<Args...>
        ;

    ///
    //////
    ////////////
    //////
    ///

    template <
        typename _pf,
        typename ...Args>
    struct select
    {
        template <typename ...Args2>
        using _select_with_pf_t = typename select<_pf, Args2...>::type;
        using _args_list = tuple_list<Args...>;
        using _select_tail = typename _args_list::template apply_tail_t<_select_with_pf_t>;

        using _f = pf<_pf>;
        static constexpr bool _is_pf_defined_at_head =
            _args_list::template apply_head_t<_f::template is_defined_at>::value;

        template <typename...>
        using _defined_result = std::tuple<typename _args_list::template apply_head_t<_f::template apply>::type>;
        template <typename...>
        using _undefined_result = std::tuple<>;

        using _head_result =
            apply_if_else_t<
                _is_pf_defined_at_head,
                _defined_result,
                _undefined_result
            >;
        using _tail_result = _select_tail;

        //
        //
        //
        using type =
            tuple_cat_t<
                _head_result,
                _tail_result
            >;
    };

    template <
        typename _pf>
    struct select<_pf>
    {
        using type = std::tuple<>;
    };

    template <typename pf, typename ...Args>
    using select_t = typename select<pf, Args...>::type;

    ///
    //////
    ////////////
    //////
    ///

    template <
        typename pf,
        typename ...Args>
    struct map:
        public select<pf, Args...>
    {
        static_assert(
            std::tuple_size_v<typename map::type> == sizeof...(Args),
            "pf is not defined for all args"
        );
    };

    template <
        typename pf,
        typename ...Args>
    using map_t = typename map<pf, Args...>::type;

    ///
    //////
    ////////////
    //////
    ///

    template <
        template <typename ...> class F,
        typename ...Args>
    struct bind
    {
        template <typename ...Args2>
        struct apply
        {
            using type = F<Args..., Args2...>;
        };
    };
}
