#pragma once
#include "record.h"

struct email: public tagged_value::data<email, std::string> { };

struct user
{
    struct id: public tagged_value::data<id, std::uint32_t> { };
    using rec = record<user, id, email>;
};
