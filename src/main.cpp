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
    { "struct", "struct" },
    { "bool", "bool" },

    { "ident", "[a-zA-Z_]+" },
    { "space", "[ ]+" },

    { "lbrace", "<" },
    { "rbrace", ">" },
    { "comma", "," },
    { "colon", ":" },
};

struct Token
{
    const TokenDefinition def;
    const std::string value;
};

namespace parse
{
    enum State
    {
        init,
    };

    struct Parser
    {
        const Tokens tokens;
        enum State state;

        void parse(std::istream& in);
        void parse_line();
    };
}
template <> struct Constructor<parse::Parser>
{
    static parse::Parser create()
    {
        return { };
    }

    static parse::Parser create(Tokens&& tokens)
    {
        return { std::move(tokens) , { } };
    }
};

int main(int, char**)
{
    auto tokens = construct<Tokens>(TokensSource);
    auto fin = std::ifstream { "src/either.x" };

    std::smatch match;
    bool error = false;

    for (std::string line; !error && std::getline(fin, line); )
        while (!line.empty()) {
            bool found = false;
            for (auto const& def: tokens.tokens)
                if (std::regex_search(cbegin(line), cend(line), match, def.rx)) {
                    auto rest = line.substr(match.length());
                    std::cout << def.name << ": " << match.str() << " || \"" << line << "\"\n";
                    line = rest;
                    found = true;
                    break;
                }
            if (!found) {
                std::cout << "NO MATCH: " << line << '\n';
                error = true;
                break;
            }
        }

    return 0;
}
