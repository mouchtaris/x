#include <iostream>
#include <type_traits>
#include <algorithm>
#include "command.h"
#include "write::tuple.h"
#include "type.h"
#include "printf.h"
#include "tagname.h"
#include "s.h"

struct poo;
using poo_t = tagged_value::data<poo, int>;

template <typename... Ts>
decltype(auto) t(Ts&&... args)
{
    return std::make_tuple(std::forward<Ts>(args)...);
}

int main(int, char**)
{
    poo_t i { 12 };
    std::cout << get(i) << '\n';
    return 0;
}
