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
#include "copy.h"
#include "json.h"
#include "async.h"
#include "async/channel.hpp"
#include "make_array.h"
#include "exp/sql.h"
#include "exp/memsql.h"
#include "talg.h"
#include "exp/memsqlrepo.h"
#include "bob.h"

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

namespace bob
{
}

//////
//
// (((x * 2) + 5)) / 2 - x
//
void async_text()
{
    using tagged_value::make;
    using async::ec::task;
    using async::ec::job;
    using async::ec::task_channel;
    using async::ec::threadpool::worker;
    auto ec = async::ec::threadpool::make<3u>();
    auto&& jb = make<job>([]() {
    });
    auto&& task_name = make<task::name>("Task1");
    auto&& tsk = make_record<task>(std::move(task_name), std::move(jb));
    ec.dispatch(std::move(tsk));
}
void count_to_xilia()
{
    for (auto i = 0; i < 1000000; ++i) {
        char const* fmt = i % 2 == 0 ? "%06X" : "%06d";
        std::ostringstream s;
        s << std::make_tuple(fmt, i) << '\n';
    }
}
int main(int, char**)
{
    async_text();

    using user_t = memsql::table<bob::user::t>;
    using user_id_c = user_t::get_column<0>;
    using user_account_id_c = user_t::get_column<1>;
    using user_name_c = user_t::get_column<2>;

    auto luser = user_t::create(
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
        // << memsql::gett<user_name_c>(luser) << nl
        // << bob::id(luser) << nl
        << "";

    memsqlrepo::repo<bob::user::t> r;

    talg::bind<std::is_same, int>::apply<int>::type b;
    std::cout
        // << tagname::of<user_id_c::is_primary_key>().at(0) << nl
        //<< talg::pred_pf<
        //        talg::bind<
        //            memsql::column_is_primary_key,
        //            name >::template apply
        //   >,
        //<< tagname::of<user_t::primary_key>().at(0) << nl
        << tagname::of<
                talg::bind<
                    std::is_same,
                    sql::sdl::primary_key
                >::apply<sql::sdl::primary_key>
                ::type

            >().at(0) << nl
        << "";

    return 0;
}
