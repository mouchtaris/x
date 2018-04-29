#pragma once
#include <string>
#include "tagname.h"
#include "tagged_value.h"

namespace type
{
    template <typename _tag>
    struct traits_for;

    template <typename _name_tag, typename _traits_tag>
    struct traits_base_t
    {
        using name_tag = _name_tag;
        using traits_tag = _traits_tag;
        using value_base_t = typename traits_for<traits_tag>::base_t;
        using value_t = tagged_value::data<name_tag, value_base_t>;

        value_t value(value_base_t v) const& { return { std::move(v) }; }
        std::string name(void) const& { return std::get<0>(tagname::of<name_tag>()); }
    };

    template <typename _tag>
    struct is_std_type
        : public std::false_type
    {
    };

#   define std_type(tag, base)                                  \
        \
        \
        struct tag##_tag_t                                      \
        {                                                       \
        };                                                      \
        \
        \
        template <>                                             \
        struct traits_for<tag##_tag_t>                          \
        {                                                       \
            using base_t = base;                                \
        };                                                      \
        \
        \
        template <typename _tag>                                \
        constexpr                                               \
        std::enable_if_t<                                       \
            std::is_base_of_v<tag##_tag_t, std::decay_t<_tag>>, \
            traits_base_t<std::decay_t<_tag>, tag##_tag_t>      \
            >                                                   \
        traits(_tag&&) { return { }; }                          \
        \
        \
        constexpr auto tag##_t = traits(tag##_tag_t { });       \
        \
        \
        template <>                                             \
        struct is_std_type<tag##_tag_t>:                        \
            public std::true_type                               \
        {                                                       \
        }

    std_type(char, char);
    std_type(uchar, unsigned char);
    std_type(short, short int);
    std_type(ushort, unsigned short int);
    std_type(int, int);
    std_type(uint, unsigned int);
    std_type(long, long int);
    std_type(ulong, unsigned long int);
    std_type(string, std::string);

    template <typename T> struct array_tag_t { };

    template <typename _tag, typename ..._fields>
    struct tuple {};
    template <typename _tag, typename ..._fields>
    struct traits_for<tuple<_tag, _fields...>> {
        using base_t = std::tuple<_fields...>;
    };

    template <typename _tag>
    using traits_t = traits_base_t<_tag, _tag>;
    template <typename tag>
    constexpr
    std::enable_if_t<
        std::negate<is_std_type<tag>>::value,
        traits_t<std::decay_t<tag>>
        >
    traits(tag&&) { return { }; }
    template <typename tag>
    constexpr traits_t<tag> traits() { return traits<tag>({}); }
    template <typename _tag>
    using traits_for_t = decltype(traits<_tag>());

}

template <
    typename _tag,
    typename _base>
std::ostream& operator <<(
    std::ostream& o, 
    tagged_value::data<_tag, _base> const& v)
{
    return o << type::traits<_tag>().name() << '{' << v.value << '}';
}
