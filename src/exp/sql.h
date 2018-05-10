#ifndef __SQL_H__
#define __SQL_H__
#include "record.h"
#include "exp/sql/sdl.h"
#include "exp/sql/is_col.h"

namespace sql
{
    template <typename T> struct create_impl;
    template <typename T, typename ...Args>
    decltype(auto) create(Args&&... args)
    {
        return create_impl<T> { }(std::forward<Args>(args)...);
    }

}
#endif // __SQL_H__
