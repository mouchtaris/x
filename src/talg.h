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
        using head = _head;
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
        typename _pf,
        typename ...Args>
    struct select
    {
        using _head = typename tuple_list<Args...>::head;

        static constexpr auto is_pf_defined_at_T = pf<_pf>::template is_defined_at<_head>::value;

        template <typename ..._tail>
        using select_with_pf = typename select<_pf, _tail...>::type;

        using tail_result = typename tuple_list<Args...>::template apply_tail_t<select_with_pf>;

        template <typename = void>
        using pf_defined_result =
            tuple_cat_t<
                std::tuple< typename pf<_pf>::template apply<_head>::type >,
                tail_result
                >;

        using pf_undefined_result = tail_result;

        using type =
            std::conditional_t<
                is_pf_defined_at_T,
                pf_defined_result<>,
                pf_undefined_result
                >;
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

    template <typename pf, typename ...Args>
    struct find
    {
        template <typename ..._Args>
        using select_pf_t = select_t<pf, _Args...>;

        using type =
            tuple_elements_t<
                select_pf_t<Args...>,
                head_t
                >
            ;
    };




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
