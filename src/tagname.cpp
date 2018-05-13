#include "tagname.h"
#include <regex>

namespace tagname {
namespace __detail
{
    namespace
    {
        const std::regex TAG_NAME_RX { "tag = ([^;]+)" };
    }

    std::string impl(std::string&& source)
    {
        std::smatch md;
        const bool found = std::regex_search(
            source,
            md,
            TAG_NAME_RX);
        if (found)
            return md[1];
        return source;
    }

}}
