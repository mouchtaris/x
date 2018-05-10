#ifndef __JSON_H__
#define __JSON_H__
#include "record.h"
#include "tuple::for_each.h"
#include <functional>

namespace json
{
    template <typename field>
    struct entry:
        public tagged_value::data<
            entry<field>,
            field>
    { };


    struct no_print_value_typ_impl {};

    template <typename value_type>
    using print_value_type_t = std::function<void (std::ostream& o, value_type const&)>;

    template <typename value_type>
    inline auto  print_value_type_impl = [](std::ostream&, value_type const&) { throw no_print_value_typ_impl { }; };

    template <>
    inline auto  print_value_type_impl<std::uint32_t> = [](std::ostream& o, std::uint32_t i) { o << i; };

    template <>
    inline auto  print_value_type_impl<std::string> = [](std::ostream& o, std::string const& s) { o << '"' << s << '"'; };


    template <typename field>
    std::ostream& dump(
        std::ostream& o,
        field const& f)
    {
        using value_t = typename field::value_t;
        try {
            print_value_type_impl<value_t>(o, get(f));
        }
        catch (no_print_value_typ_impl) {
            std::array<std::string, 1>&& tags = tagname::of<value_t>();
            auto&& type = std::get<0>(tags);
            o << " X X X X X X  ----- no implementation for dump( " << type << " ) ------- XXX X X X X X X\n";
        }
        return o;
    }

    template <typename field>
    auto dump(
        std::ostream& o,
        field const& f)
    ->
        std::enable_if_t<
            std::is_same_v<typename field::value_t, std::uint32_t> && false,
            std::ostream&>
    {
        return o << get(f);
    }

    template <
        typename field
        >
    void dump(std::ostream& o, entry<field> const& e, bool is_last)
    {
        const auto& names = tagname::of<typename field::Tag>();
        o << '"' << names.at(0) << "\": ";
        dump(o, get(e));
        if (!is_last)
            o << ',';
        o << '\n';
    }

    template <
        typename tag,
        typename ...fields>
    void dump(std::ostream& o, record<tag, fields...> const& r)
    {
        o << "{\n";
        auto&& print_entry = [&o](auto data, bool is_last)
        {
            using field_t = std::decay_t<decltype(data)>;
            auto&& en = tagged_value::make<entry<field_t>>(std::move(data));
            o << "  ";
            dump(o, std::move(en), is_last);
        };
        for_each(get(r), std::move(print_entry), std::index_sequence_for<fields...> { });
        o << "}\n";
    }

}
#endif // __JSON_H__
