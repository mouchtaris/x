#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <regex>

using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::get;
using std::rbegin;
using std::rend;
using namespace std::placeholders;

#include "construct.hpp"
#include "tokens.hpp"

constexpr std::initializer_list<std::tuple<char const*, char const*>> TokensSource = {
    { "ident", "\\w+" },
    { "space", "\\s+" },
    { "lbrace", "<" },
    { "rbrace", ">" }
};

int main(int, char**)
{
    for (auto const& def: construct<Tokens>(TokensSource).tokens)
        std::cout << def.name << '\n';
    return 0;
}
