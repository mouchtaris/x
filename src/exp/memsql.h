#pragma once
#include "exp/sql.h"
#include "talg.h"
#include "record.h"
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
        using native_t = std::string;
    };

    ///
    //////
    /////////
    //////
    ///

    namespace tag
    {
        template <typename name> struct column_value;
        template <typename name> struct table_value;
    }

    ///
    //////
    /////////
    //////
    ///

    struct is_col_pf
    {
        template <typename T>
        struct _detail
        {
            template <typename ...cols>
            using is_col_f = std::disjunction< std::is_same<T, cols> ... >;

            using is_col = sql::sdl::col::apply_cols_t<is_col_f>;
        };

        template <typename T>
        struct is_defined_at:
            public _detail<T>::is_col
        { };

        template <typename T>
        struct apply
        {
            using type = typename _detail<T>::is_col;
        };
    };

    template <
        typename _name,
        typename ..._attrs>
    struct column<sql::sdl::column<_name, _attrs...>>
    {
        using name      = _name;

        using type      = talg::find_t<is_col_pf, _attrs...>;
        using native_t  = typename column<type>::native_t;
        using tagged_t  = tagged_value::data<tag::column_value<name>, native_t>;

        static tagged_t     create(native_t v) { return tagged_value::make<tagged_t>(std::move(v)); }
    };

    ///
    //////
    /////////
    //////
    ///

    template <typename _table> struct table;
    template <
        typename name,
        typename ...columns>
    struct table<sql::sdl::table<name, columns...>>
    {
        struct value
        {
            using rec = record<tag::table_value<name>, typename column<columns>::tagged_t ... >;
        };

        template <size_t i>
        using get_column = column<std::tuple_element_t<i, std::tuple<columns...>>>;

        template <typename ...Args>
        static typename value::rec create(Args&&... args)
        {
            return make_record<value>(std::forward<Args>(args) ...);
        }
    };

    template <
        typename _column,
        typename _table_name,
        typename ..._values>
    auto const& gett(record<memsql::tag::table_value<_table_name>, _values...> const& r)
    {
        return ::gett<typename _column::tagged_t>(r);
    }
}

