#include <iostream>
#include <functional>
#include <type_traits>
#include <thread>
#include <utility>
#include <limits>
#include <memory>
#include <new>

#include "optional_to_string.hpp"

using std::get;
using std::begin;
using std::end;
using std::rbegin;
using std::rend;
using std::nullopt;


template <typename A, typename B, typename C>
std::ostream& operator << (std::ostream& o, std::tuple<A, B, C> const& t)
    { return o << "tuple3[" << get<0>(t) << ',' << get<1>(t) << ',' << get<2>(t) << ']'; }

template <
    typename T,
    typename = decltype(std::numeric_limits<T>::max()),
    typename = decltype(std::declval<T>() > std::declval<T>()),
    typename = decltype(std::declval<T>() - std::declval<T>()),
    typename = decltype(std::declval<T>() + std::declval<T>())
>
std::optional<std::tuple<T, T, T>> fnext(const std::tuple<T, T, T> t)
{
    const auto from = get<0>(t);
    const auto to = get<1>(t);
    const auto step = get<2>(t);
    const auto max = std::numeric_limits<T>::max();

    if (from > max - step)
        return nullopt;

    const auto next = from + step;

    if (next > to)
        return nullopt;

    return std::make_tuple ( next, to, step );
}







template <
    typename A,
    typename F,
    typename B = std::invoke_result_t<F, A>
> std::optional<B> fmap(std::optional<A> opt, F f)
{
    if (opt.has_value())
        return std::invoke(std::move(f), opt.value());
    return std::nullopt;
}







template <
    typename T,
    typename ...Args
> T& inplace(T& obj, Args&&... args)
{
    using Allocator = std::allocator<T>;
    using Traits = std::allocator_traits<Allocator>;
    using PTraits = std::pointer_traits<T*>;
    using Ptr = typename PTraits::pointer;

    Allocator allocator = { };
    const Ptr ptr = PTraits::pointer_to(obj);
    Traits::construct(allocator, ptr, std::forward<Args>(args)...);
}








struct Range {
    int from, to, step;

    static constexpr int DEFAULT_STEP = 1;
    static constexpr Range create(int from, int to, int step)
        { return { from, to, step }; }
    static constexpr Range create(int from, int to)
        { return create(from, to, DEFAULT_STEP); }
    static Range fromTuple(std::tuple<int, int, int> t)
        { return create(get<0>(t), get<1>(t), get<2>(t)); }

    Range withFrom(int from) const { return { from, to, step }; }
    Range withTo(int to) const { return { from, to, step }; }
    Range withStep(int step) const { return { from, to, step }; }
};

std::ostream& operator << (std::ostream& out, Range r)
    { return out << "Range[from=" << r.from << ",to=" << r.to << ",step=" << r.step << ']'; }

std::tuple<int, int, int> toTuple(Range r) { return { r.from, r.to, r.step }; }

std::optional<Range> fnext(const Range r)
{
    return fmap(
        fnext(toTuple(r)),
        &Range::fromTuple
    );
}






template <
    typename T,
    typename C,
    typename = decltype(fnext(std::declval<T>())),
    typename = decltype(std::declval<C>()(std::declval<T>()))
> void foreach(T traversable, C callback)
{
    callback(traversable);
    std::optional<T> next = fnext(std::move(traversable));
    if (next.has_value())
        foreach(next.value(), std::move(callback));
}







int main(int, char**) {
    auto&& println = [](auto&& wat) -> std::ostream& { return std::cout << wat << '\n'; };
    auto&& tup = std::make_tuple(1, 8, 3);
    auto&& r = Range::create(1, 5);
    foreach(tup, println);
    foreach(r, println);

    auto&& opt = std::optional<int> { 18 };
    auto&& opt2 = fmap(opt, [](int i) { return i + 1; });
    std::cout 
        << opt << '\n'
        << opt2 << '\n'
        << fnext(std::make_tuple(1, 5, 3)) << '\n'
        ;



    return 0;
}

