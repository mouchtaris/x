#pragma once
#include <array>
#include <string>

namespace tagname
{
    namespace __detail {
        extern std::string impl(std::string&&);

        template <typename tag>
        inline std::string tagname() { return impl(__PRETTY_FUNCTION__); }
    }

    template <typename ...tags>
    auto of()
        -> std::array<std::string, sizeof...(tags)>
    {
        return {
            __detail::tagname<tags>() ... ,
        };
    }
}
