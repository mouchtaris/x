#pragma once
#include "exp/sql.h"
#include "talg.h"
#include <cstdint>
#include <string>

namespace memsql
{
    template <typename C> struct column;

    template <>
    struct column<sql::sdl::col::Int>
    {
        using native_t = std::int32_t;
    };

    template <>
    struct column<sql::sdl::col::String>
    {
        using native_t = std::wstring;
    };



    template <typename _column> struct column;
    template <
        typename _name,
        typename ..._attrs>
    struct column<sql::sdl::column<_name, _attrs...>>
    {
        using name = _name;
        template <template <typename...> class F>
        using apply_attributes_t = F<_attrs...>;
    };



    template <typename _table> struct table;
    template <
        typename _name,
        typename ...columns>
    struct table<sql::sdl::table<_name, columns...>>
    {
        using name = _name;

        template <template <typename...> class F>
        using apply_columns_t = F<columns...>;
    };

    template <
        typename _table>
    struct table_value
    {
        struct to_native_type
        {
            template <typename T>
            struct is_defined_at:
                public std::conditional_t<
                    std::is_default_constructible_v<column<T>>,
                    std::true_type,
                    std::false_type
                >
            { };

            template <typename T>
            struct apply
            {
                template <typename = void> using defined_type = typename column<T>::native_t;
                using undefined_type = void;

                using type =
                    std::conditional_t<
                        is_defined_at<T>::value,
                        defined_type<>,
                        undefined_type
                    >;
            };
        };

        template <typename ...Args>
        using map_to_native_type = talg::map_t<to_native_type, Args...>;

        using type = typename table<_table>::template apply_columns_t<map_to_native_type>;
    };
}
