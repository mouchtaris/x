#include <iostream>
#include <type_traits>
#include <algorithm>
#include <cstdint>
#include <sstream>
#include "tagged_value/write.h"
#include "write::tuple.h"
#include "type.h"
#include "printf.h"
#include "s.h"
#include "model.h"
#include "copy.h"
#include "json.h"
#include "async.h"
#include "async/channel.hpp"
#include "make_array.h"
#include "exp/sql.h"
#include "exp/memsql.h"
#include "talg.h"

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

namespace bob
{
    using namespace sql::sdl;

    struct account 
    {
        struct id;
        struct email;

        using t = table<account,
            column<id       , col::Int      >,
            column<email    , col::String   >
        >;
    };

    struct user
    {
        struct id;
        struct account_id;
        struct name;

        using t = table<user,
            column< id          , col::Int          >,
            column< account_id  , col::Int          >,
            column< name        , col::String       >
        >;
    };
}

using tagged_value::make;
using async::ec::task;
using async::ec::job;
using async::ec::task_channel;
using async::ec::threadpool::worker;
//////
//
//
struct bab
{
    template <typename T> struct is_defined_at:
        public std::conditional_t<
            std::is_same_v<T, float>,
            std::false_type,
            std::true_type
            >
        { };
    template <typename T> struct apply
    {
        using type = std::tuple<T>;
    };
};
//////
//
// (((x * 2) + 5)) / 2 - x
//
void count_to_xilia() {
    for (auto i = 0; i < 1000000; ++i) {
        char const* fmt = i % 2 == 0 ? "%06X" : "%06d";
        std::ostringstream s;
        s << std::make_tuple(fmt, i) << '\n';
    }
}
int main(int, char**)
{
    auto ec = async::ec::threadpool::make<3u>();
    auto&& jb = make<job>([]() {
    });
    auto&& task_name = make<task::name>("Task1");
    auto&& tsk = make_record<task>(std::move(task_name), std::move(jb));
    ec.dispatch(std::move(tsk));

    std::cout
        << tagname::of<talg::select_t<bab, int, double, float, void, char, bool>>().at(0) << nl
        << tagname::of<talg::map_t<bab, int, double, void, char, bool>>().at(0) << nl
        << tagname::of<talg::map_t<bab, int, double, void, char, bool>>().at(0) << nl
        << tagname::of<talg::find_t<talg::is_same_pf<double>, int, double, void, char, bool>>().at(0) << nl
        << tagname::of<typename memsql::table<typename bob::user::t>::value>().at(0) << nl
        << "";

    using user_t = memsql::table<bob::user::t>;
    using user_id_c = user_t::get_column<0>;
    using user_account_id_c = user_t::get_column<1>;
    using user_name_c = user_t::get_column<2>;

    auto&& luser = user_t::create(
        user_id_c::create(12),
        user_account_id_c::create(28),
        user_name_c::create("LOL")
    );
    //write::tuple(std::cout, luser) << nl;
    auto&& id_v = user_id_c::create(12);
    auto&& account_id_v = user_account_id_c::create(28);
    auto&& name_v = user_name_c::create("PAP");
    std::cout
        << id_v << nl
        << account_id_v << nl
        << name_v << nl
        << memsql::gett<user_name_c>(luser) << nl
        << "";

    return 0;
}
