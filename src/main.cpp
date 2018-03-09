#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <thread>
#include <type_traits>
#include <utility>

#include "optional_to_string.hpp"
#include "pretty_print_tuple.hpp"

using std::begin;
using std::end;
using std::get;
using std::nullopt;
using std::rbegin;
using std::rend;

template <typename T> void pig(T) { puts(__PRETTY_FUNCTION__); }

struct str
{
    char const* data;
    std::size_t begin, end;
};
static_assert(std::is_trivial_v<str>, "");

namespace either
{
    template <typename L, typename R> struct Either;
    template <typename L, typename R> struct Ops;
    template <typename L, typename R> Ops<L, R> make_ops(Either<L, R>&);
    template <typename Side> struct SideTraits;

    template <typename L, typename R>
    struct Either
    {
        bool is_left;
        std::aligned_union_t<0, L, R> data;

        Either() = delete;
        Either(Either const&) = delete;

        Either(bool l): is_left { l }, data { } { }
        Either(Either&& other): Either(other.is_left) { make_ops(*this).moved_from(std::move(other)); }

        void operator =(Either const&) = delete;
        void operator =(Either&&) = delete;

        ~Either() { make_ops(*this).destroy(); }
    };

    template <typename L, typename R> using E = Either<std::decay_t<L>, std::decay_t<R>>;

    template <typename L, typename R>
    struct Ops
    {
        E<L, R>& either;

        void* data() { return std::addressof(either.data); }
        L* left_data() { return reinterpret_cast<L*>(data()); }
        R* right_data() { return reinterpret_cast<R*>(data()); }

        void moved_from(E<L, R>&& other)
        {
            auto other_ops = make_ops(other);

            if (either.is_left)
                new(left_data()) L(std::move(*other_ops.left_data()));
            else
                new(right_data()) R(std::move(*other_ops.right_data()));
        }
        void destroy()
        {
            if (either.is_left)
                std::destroy_at(left_data());
            else
                std::destroy_at(right_data());
        }
    };
    template <typename L, typename R> Ops<L, R> make_ops(Either<L, R>& either) { return { either }; }

    struct Side {};
    struct Left: public Side { };
    struct Right: public Side { };

    template <> struct SideTraits<Left>
    {
        template <typename L, typename R> using Arg = L;
        static constexpr bool is_left = true;
        template <typename L, typename R> static L* data(Ops<L, R> ops) { return ops.left_data(); }
    };
    template <> struct SideTraits<Right>
    {
        template <typename L, typename R> using Arg = R;
        static constexpr bool is_left = false;
        template <typename L, typename R> static R* data(Ops<L, R> ops) { return ops.right_data(); }
    };

    template <
        typename L,
        typename R,
        typename Side,
        typename Alloc = std::allocator<typename SideTraits<Side>::template Arg<L, R>>
    > struct Constructor
    {
        using ST = SideTraits<Side>;

        Alloc& allocator;
        std::allocator_traits<Alloc> talloc;

        E<L, R> create() { return { ST::is_left }; }

        template <typename A>
        E<L, R> construct(E<L, R>&& either, A&& a)
        {
            auto ops = make_ops(either);
            auto data = ST::data(ops);
            talloc.construct(allocator, data, std::forward<A>(a));
            return std::move(either);
        }

        template <typename A>
        E<L, R> operator () (A&& a)
        {
            return construct(create(), std::forward<A>(a));
        }
    };

    template <
        typename L,
        typename R,
        typename Side,
        typename Alloc = std::allocator<typename SideTraits<Side>::template Arg<L, R>>
        >
    Constructor<L, R, Side, Alloc> constructor(Alloc&& alloc)
        { return { alloc, { } }; }


    template<
        typename R,
        typename L,
        typename Alloc = std::allocator<L>
        >
    E<L, R> left(L&& l, Alloc&& alloc = Alloc { })
    {
        return constructor<L, R, Left>(std::forward<Alloc>(alloc))(std::forward<L>(l));
    }

    template<
        typename L,
        typename R,
        typename Alloc = std::allocator<R>
        >
    E<L, R> right(R&& r, Alloc&& alloc = Alloc { })
    {
        return constructor<L, R, Right>(std::forward<Alloc>(alloc))(std::forward<R>(r));
    }
}

struct A {
    bool moved = false;
    A() = default;
    A(A&& a) { a.moved = true; }
    ~A() { if (!moved) std::cout << " You should see this once \n"; }
};

int main(int, char**) {
    auto&& p = [](auto&& wat) { std::cout << wat << '\n'; };
 
    p( std::is_trivial_v<std::aligned_union_t<0, int, float>> );

    either::left<float>(A { });
    either::right<int>(A { });
    either::left<A>(std::string("fu"));

    return 0;
}

