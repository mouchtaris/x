#include <iostream>
#include <type_traits>
#include <algorithm>
#include <cstdint>
#include "command.h"
#include "write::tuple.h"
#include "type.h"
#include "printf.h"
#include "s.h"
#include "model.h"
#include "copy.h"
#include "json.h"

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
//
//
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
    auto j  = konst(make<json::entry<user::id>>(id()));
    auto u  = konst(make_record<user>(t(id(), em())));
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
        << vs::j () << nl
        << vs::u () << nl
        << nl
        << nl
        << "";
    json::dump(std::cout, vs::j());
    std::cout 
        << nl
        << nl;
    json::dump(std::cout, vs::u());

    return 0;
}
