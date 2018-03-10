#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <regex>
#include <optional>

using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::get;
using std::rbegin;
using std::rend;
using std::move;
using std::forward;
using std::getline;
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
    constexpr char const* StateNames[] = {
        "init",
    };

    struct Parser
    {
        const Tokens tokens;
        std::istream& ins;

        enum State state;
        std::optional<std::string> error;
        std::string line;
        Token token;

        bool __dummy;

        Parser(Tokens&& tokens, std::istream& ins):
            tokens { move(tokens) },
            ins { ins },
            state { State::init },
            error { std::nullopt },
            line { },
            token { },
            __dummy { false }
            { }


        struct ParseAutoContext
        {
            std::function<void ()> pre, post;
            inline void operator() (ParseAutoContext const&) { }
        };

        bool has_error() const;

        void parse();
        bool is_end();
        bool parse_line();
        bool fill_line_buffer();
        void pre_parse_hook();
        void post_parse_hook();

        bool parse_ident();
        void consume_space();

    };

#   define  CTX     ParseAutoContext _parse_auto_context = {\
                        [this] () { pre_parse_hook(); }, \
                        [this] () { post_parse_hook(); } \
                    }; \
                    _parse_auto_context(_parse_auto_context)

    void Parser::post_parse_hook()
    {
    }

    void Parser::pre_parse_hook()
    {
        consume_space();
    }

    bool Parser::fill_line_buffer()
    {
        if (!line.empty())
            return true;

        if (!ins)
            return false;

        getline(ins, line);

        return !!ins;
    }

    bool Parser::parse_line()
    {
        return 
            fill_line_buffer() &&
            parse_ident() &&
            true;
    }

    void Parser::parse()
    {
        while (!is_end())
            parse_line();
    }

    bool Parser::has_error() const
    {
        return error.has_value();
    }
}

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
