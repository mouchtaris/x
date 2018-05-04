#include <iostream>
#include <type_traits>
#include <algorithm>
#include <cstdint>
#include "write::tuple.h"
#include "type.h"
#include "printf.h"
#include "s.h"
#include "model.h"
#include "copy.h"
#include "json.h"
#include "async.h"

//////
//
//
//
constexpr auto nl = '\n';
template <typename tag>
void ptag(std::ostream& o = std::cout)
{
    o << "tagname:[";
    for (auto el: tagname::of<tag>())
        o << el << ',';
    o << "]\n";
}

//////
//
//
//
template <typename... Ts>
decltype(auto) t(Ts&&... args)
{
    return std::make_tuple(std::forward<Ts>(args)...);
}

//////
//
//
//
#include <future>
#include <mutex>
namespace view
{
    template <
        typename C,
        typename F>
    struct map_t
    {
        std::reference_wrapper<const C> cont;
        F f;
    };

    template <
        typename C,
        typename F>
    struct map_iter_t
    {
        using iter_t = std::decay_t<decltype(begin(std::declval<C>()))>;
        iter_t i;
        F f;

        decltype(auto) operator != (map_iter_t const& other) const& { return i != other.i; }
        decltype(auto) operator * () const& { return f(*i); }
        void operator++() { ++i; }

    };

    template <
        typename C,
        typename F>
    map_iter_t<C, F> begin(map_t<C, F> const& m)
    {
        return {
            begin(m.cont.get()),
            m.f
        };
    }

    template <
        typename C,
        typename F>
    map_iter_t<C, F> end(map_t<C, F> const& m)
    {
        return {
            end(m.cont.get()),
            m.f
        };
    }

    template <
        typename T,
        typename F>
    auto map(std::vector<T> const& vec, F&& f)
    {
        return map_t<std::vector<T>, F> {
            std::ref(vec),
            std::move(f)
        };
    }
}
namespace like
{
    template <typename> struct future_t;
    template <typename T> struct future_t<std::future<T>>
    {
        using self_t = std::future<T>;
        self_t& self;
    };

    template <typename T>
    future_t<T> future(T& t)
    {
        return { t };
    }

}
namespace async
{
    auto lock(std::mutex& m)
    {
        return std::lock_guard<std::mutex> { m };
    }

}

//////
//
//
//
namespace vs
{
    using tagged_value::make;
    const auto konst = [](auto v){ return [v](){ return v; }; };

    auto id = konst(make<user::id>(12u));
    auto em = konst(make<email>("lol"));
    auto u  = konst(make_record<user>(t(id(), em())));
}
//////
//
//
//
namespace repo
{
    struct id: public tagged_value::data<id, std::uint64_t> { };

    template <typename R>
    using items_t = std::vector<typename R::rec>;

    template <typename R>
    struct data:
        public tagged_value::data<
            data<R>,
            std::tuple< std::mutex, items_t<R> >
            >
    { };

    template <typename R>
    std::mutex& mutex(data<R>& d) { return std::get<0>(get(d)); }

    template <typename R>
    items_t<R>& items(data<R>& d) { return std::get<1>(get(d)); }

    template <typename R>
    using data_t = data<R>;

    template <typename R>
    struct addjob
    {
        using rep_t = std::reference_wrapper<data_t<R>>;
        using rec_t = typename R::rec;
        using prom_t = std::promise<id>;
        static_assert(std::is_move_constructible_v<rep_t>, "");
        static_assert(std::is_move_constructible_v<rec_t>, "");
        static_assert(std::is_move_constructible_v<prom_t>, "");

        rep_t rep_ref;
        rec_t rec;
        prom_t done;

        void operator()()
        {
            data_t<R>& rep = rep_ref.get();

            std::mutex& m = mutex(rep);
            auto&& _lock = async::lock(m);

            items_t<R>& v = items(rep);
            v.emplace_back(std::move(rec));

            auto&& i = tagged_value::make<id>(v.size() - 1);
            done.set_value(std::move(i));
        }
    };

    template <typename R>
    std::future<id> add(data_t<R>& rep, typename R::rec&& rec)
    {
        auto&& done_promise = std::promise<id> { };
        auto&& done_future = done_promise.get_future();
        auto&& job = addjob<R> { std::ref(rep), std::move(rec), std::move(done_promise) };
        std::thread { std::move(job) }.detach();
        return std::move(done_future);
    }


}


//////
//
// (((x * 2) + 5)) / 2 - x
//
int main(int, char**)
{
    ptag<user>();
    ptag<user::id>();
    ptag<user::id::base_t>();

    std::cout 
        << vs::id() << nl
        << vs::em() << nl
        << vs::u () << nl
        << nl
        << nl
        << "";
    json::dump(std::cout, vs::u());

    auto&& u = vs::u();
    std::cout
        << gett<email>(u) << nl
        << gett<user::id>(u) << nl
        << "";

    auto v = std::vector { 1, 2, 3 };
    auto&& plus1 = [](int i) { return i + 1; };
    auto vp1 = view::map(v, std::move(plus1));
    for (auto&& el: vp1)
        std::cout << el << nl;

    std::vector<std::future<repo::id>> futie;
    auto&& user_repo = tagged_value::make<repo::data_t<user>>();
    for (user::id::value_t i = 0; i < 100; ++i) {
        auto&& u = make_record<user>(
            tagged_value::make<user::id>(i + 20),
            tagged_value::make<email>("lol@email.com")
            );
        futie.emplace_back(repo::add(user_repo, std::move(u)));
    }

    for (std::size_t i = 0; i < futie.size(); ++i) {
        auto& add_user_done = futie.at(i);
        std::cout << "waiting for user #" << i << " to be added..." << nl;
        add_user_done.wait();
        std::cout << "waiting for user #" << i << " to be added is done ... id = " << add_user_done.get() << nl;
    }

    return 0;
}
