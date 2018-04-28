#include "command.h"
#include <regex>
#include <cstring>

namespace
{
    std::regex COMMAND_NAME_RX { "tag = ([^;]+)" };
}

namespace command
{

    std::string __command_name(char const* pretty_function)
    {
        const std::string source { pretty_function };
        std::smatch md;
        const bool found = std::regex_search(
            begin(source),
            end(source),
            md,
            COMMAND_NAME_RX);
        if (found)
            return md[1];
        return "";
    }

}
