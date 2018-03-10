#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using std::begin;
using std::end;
using std::get;
using std::rbegin;
using std::rend;

constexpr std::initializer_list<std::tuple<char const*, char const*>> TokensSource = {
    { "ident", "\\w+" },
    { "space", "\\s+" },
};

using TokenDefinition = std::tuple<std::string, std::regex>;
using Tokens =   
struct Tokens
{
    std::vector<TokenDefinition> tokens;
};

void reads() {
    std::istringstream sin { "hello\ni am bob\n" };
    std::ifstream fin { "src/either.x" };
    std::string line;
    while (sin) {
        std::getline(sin, line);
        std::cout << " Line: " << line <<'\n';
    }
    while (fin) {
        std::getline(fin, line);
        std::cout << "FLine: " << line << '\n';
    }
}

int main(int, char**)
{
    reads();
    return 0;
}
