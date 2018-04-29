#pragma once
#include <array>
#include <tuple>
#include <cstdio>
#include <cstring>
#include <functional>

namespace sprint
{
    template <size_t bs>
    using buf_t = std::array<char, bs>;

    template <size_t bs>
    struct view_t
    {
        std::reference_wrapper<buf_t<bs>>   buf;
        std::size_t                         at;
    };

    template <size_t bs> constexpr inline
    std::size_t size(view_t<bs>)
    {
        return bs;
    }

    template <size_t bs> constexpr inline
    std::size_t free(view_t<bs> v)
    {
        return size(v) - v.at;
    }

    template <size_t bs> constexpr
    bool can_fit(view_t<bs> v, std::size_t s)
    {
        return free(v) > s;
    }

    template <size_t bs> constexpr
    char* data(view_t<bs> v)
    {
        return v.buf.get().data();
    }




    template <size_t bs>
    view_t<bs> view(buf_t<bs>& buf, std::size_t at)
    {
        return { ref(buf), at };
    }

    template <size_t bs>
    view_t<bs> view(buf_t<bs>& buf)
    {
        return view(buf, 0);
    }




    template <size_t bs>
    void blackout(view_t<bs> v)
    {
        std::memset(data(v), 'x', bs);
    }




    template <size_t bs>
    bool s(view_t<bs> v, char const* fmt, int i)
    {
        const auto bufsize = free(v);
        const auto whbw = std::snprintf(data(v), bufsize, fmt, i);
        return
            whbw > 0 &&
            static_cast<decltype(bufsize)>(whbw) < bufsize; // signedness warning
    }
}
