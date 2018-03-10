#pragma once

#include <string>
#include <regex>

#include "tokens.h"
#include "typetype.hpp"

struct TokenDefinition
{
    std::string name;
    std::regex rx;
};

template <> struct Constructor<TokenDefinition>
{
    static TokenDefinition create(char const* name, char const* rx);
};

struct Tokens
{
    std::map<
        fieldtype(TokenDefinition, name),
        TokenDefinition
    > tokens;
};

template <> struct Constructor<Tokens>
{
    static Tokens create(size_t size);
    static Tokens create(std::initializer_list<std::tuple<char const*, char const*>> defs);
};
