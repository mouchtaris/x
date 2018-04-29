#include <iostream>
#include <type_traits>
#include <algorithm>
#include "command.h"
#include "write::tuple.h"
#include "type.h"
#include "tagname.h"

struct name: public type::string_tag_t {
    static name t;
};
name name::t;

struct id: public type::uint_tag_t {
    static id t;
};
id id::t;

struct user {};
using user_t = type::tuple<user, id, name>;

int main(int, char**)
{
    type::traits(id::t);
    return 0;
}
