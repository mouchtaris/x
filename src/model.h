#pragma once
#include "record.h"

struct email: public tagged_value::data<email, std::string> { };


template <
    typename rec,
    typename ...Args>
typename rec::rec make_record(Args&&... args)
{
    return {
        typename rec::rec::base_t {
            typename rec::rec::value_t {
                std::forward<Args>(args)...
            }
        }
    };
}


struct user
{
    struct id: public tagged_value::data<id, std::uint32_t> { };
    using rec = record<user, id, email>;
};
