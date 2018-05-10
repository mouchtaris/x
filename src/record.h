#ifndef __RECORD_H__
#define __RECORD_H__
#include <tuple>
#include "tagged_value.h"

template <
    typename tag,
    typename ...fields
    >
struct record:
    public tagged_value::data<tag, std::tuple<fields...>>
{ };

template <
    size_t index,
    typename tag,
    typename ...fields>
struct __record__get_from_index_impl
{
    decltype(auto) operator () (record<tag, fields...> const& rec)
    {
        return std::get<index>(tagged_value::get(rec));
    }
};

template <
    size_t index,
    typename field,
    typename tag,
    typename ...fields>
struct __record__get_field_impl:
    public std::conditional_t<
        std::is_same_v<field, std::tuple_element_t<index, std::tuple<fields...>>>,
        __record__get_from_index_impl<index, tag, fields...>,
        __record__get_field_impl<index + 1, field, tag, fields...>
        >
{
};

template <
    typename field,
    typename tag,
    typename ...fields>
decltype(auto) gett(record<tag, fields...> const& rec)
{
    return __record__get_field_impl<0, field, tag, fields...> { }(rec);
}

template <
    typename R,
    typename ...Args>
decltype(auto) make_record(Args&&... args)
{
    return typename R::rec {
        typename R::rec::base_t {
            typename R::rec::value_t {
                std::forward<Args>(args) ...
            }
        }
    };
}
#endif // __RECORD_H__
