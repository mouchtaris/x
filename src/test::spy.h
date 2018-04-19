#pragma once
#include <string>
#include "dbg.h"
#include "no_copy.h"
namespace test {
    struct spy {
        const std::string name;
        bool called = false;
        void operator () () {
            dblog((
                std::string("calling spy: ") +
                name
            ).c_str());
            called = true;
        }
    };
}
