#include <iostream>
#include <tuple>
#include <type_traits>
#include <initializer_list>
#include <functional>
#include <utility>
#include "tagname.h"

template <
    typename T,
    typename V>
using forward_t = decltype(std::forward<T>(std::declval<V>()));

template <
    typename T,
    typename M>
struct forward_member
{
    using type = std::remove_reference_t<M>;
};
template <
    typename T,
    typename M>
struct forward_member<T&, M>
{
    using type = std::remove_reference_t<M>&;
};
template <
    typename T,
    typename M>
using forward_member_t = typename forward_member<T, M>::type;



template <
    typename,
    typename = std::void_t<>>
struct is_well_formed:
    public std::false_type
{
};

template <
    template <typename ...> class F,
    typename ...Args>
struct is_well_formed<std::void_t<>, F<Args...>>:
    public std::true_type
{
};


template <
    typename ...ts>
auto t(ts&&... args)
{
    return std::tuple< std::decay_t<ts> ... > {
        std::forward<ts>(args)...
    };
}

template <
    typename tag,
    typename T>
struct tv
{
    T v;
};

template <
    typename T>
struct as_tv
{
    using is = std::false_type;
    using type = std::void_t<>;
};

template <
    typename _tag,
    typename _type>
struct as_tv<tv<_tag, _type>>
{
    using is = std::true_type;
    using tag = _tag;
    using type = _type;
};

template <
    typename T>
auto get(T&& t)
    -> std::enable_if_t<
        as_tv<std::decay_t<T>>::is::value,
        forward_member_t<
            forward_t<T, decltype(t)>,
            typename as_tv<std::decay_t<T>>::type
        >
    >
{
    return t.v;
}

using tests_t = const std::initializer_list<std::tuple<char const*, std::function<bool()>>>;
tests_t tests = {
    t("tv value eq original value", []() {
        struct age;
        static_assert(::tv<age, int> { 12 }.v == 12, "");
        return true;
    }),
    t("assigning same base-value tv-s to different tag tv-s is not well formed", []() {
        struct tag1;
        struct tag2;
        struct val_t { };
        using tv1_t = tv<tag1, val_t>;
        using tv2_t = tv<tag2, val_t>;
        static_assert(!std::is_assignable_v< tv1_t, tv2_t >, "");
        return true;
    }),
    t("assigning same tag tv-s to different base-value tv-s is not well formed", []() {
        struct tag;
        struct val1_t { };
        struct val2_t { };
        using tv1_t = tv<tag, val1_t>;
        using tv2_t = tv<tag, val2_t>;
        static_assert(!std::is_assignable_v< tv1_t, tv2_t >, "");
        return true;
    }),
    t("tv is assignable", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        static_assert(std::is_assignable_v< tv_t, tv_t >, "");
        return true;
    }),
    t("as_tv::is for non tv-types is false", []() {
        static_assert( std::is_base_of_v< std::false_type, as_tv<int>::is >, "");
        return true;
    }),
    t("as_tv::is for tv-types is true", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        using as_tv_t = as_tv<tv_t>;
        using is = as_tv_t::is;
        static_assert( std::is_base_of_v< std::true_type, is >, "");
        return true;
    }),
    t("as_tv::type for tv-types is T", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        using as_tv_t = as_tv<tv_t>;
        using type = as_tv_t::type;
        static_assert( std::is_same_v< val_t, type >, "");
        return true;
    }),
    t("get(tv&) is of type T&", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        using get_t = decltype(get(std::declval<tv_t&>()));
        static_assert( std::is_same_v< get_t, val_t& >, "");
        return true;
    }),
    t("get(tv) is of type T", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        using get_t = decltype(get(std::declval<tv_t>()));
        static_assert( std::is_same_v< get_t, val_t >, "");
        return true;
    }),
    t("get(tv&&) is of type T", []() {
        struct tag;
        struct val_t { };
        using tv_t = tv<tag, val_t>;
        using get_t = decltype(get(std::declval<tv_t&&>()));
        static_assert( std::is_same_v< get_t, val_t >, "");
        return true;
    }),
};
void run(tests_t tests)
{
    for (auto& [n, t]: tests)
        std::cerr << "Running " << n << " . . . "
            << (t() ? "ok" : "fail")
            << '\n';
}

constexpr auto nl = '\n';
int main(int, char**)
{
    run(tests);
    return 0;
}
