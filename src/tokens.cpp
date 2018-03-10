#include "tokens.hpp"

TokenDefinition Constructor<TokenDefinition>::create(
    char const* name,
    char const* rx
) {
    return {
        name,
        std::regex(std::string("^") + rx)
    };
}

Tokens Constructor<Tokens>::create(size_t size)
{
    return { std::vector<TokenDefinition>(size) };
}

Tokens Constructor<Tokens>::create(std::initializer_list<std::tuple<char const*, char const*>> defs)
{
    auto make_def = [](auto& tup) {
        return std::apply(&Constructor<TokenDefinition>::create, tup);
    };

    auto result = create(defs.size());

    std::transform(
        begin(defs),
        end(defs),
        begin(result.tokens),
        make_def
    );

    return result;
}
